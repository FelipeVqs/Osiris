#pragma once

#include <array>
#include <cstddef>
#include <memory>
#include <vector>

#include <FeatureHelpers/HudInWorldPanelIndex.h>
#include <FeatureHelpers/HudInWorldPanels.h>
#include <FeatureHelpers/PanoramaTransformations.h>
#include <FeatureHelpers/Sound/SoundWatcher.h>
#include <FeatureHelpers/TogglableFeature.h>
#include <Hooks/ViewRenderHook.h>
#include "SoundVisualization.h"
#include "SoundVisualizationPanelFactory.h"

using namespace FeatureHelpers;
using namespace Hooks;

struct SoundVisualizationFeatureState {
    bool enabled{false};

    cs2::PanelHandle containerPanelHandle;
    std::vector<HudInWorldPanelIndex> panelIndices;
};

template <typename PanelsType, typename SoundType>
class SoundVisualizationFeature : public TogglableFeature<SoundVisualizationFeature<PanelsType, SoundType>> {
public:
    SoundVisualizationFeature(
        SoundVisualizationFeatureState& state,
        HookDependencies& hookDependencies,
        ViewRenderHook& viewRenderHook,
        SoundWatcher<SoundType>& soundWatcher,
        HudInWorldPanelContainer& hudInWorldPanelContainer,
        WorldToClipSpaceConverter& worldtoClipSpaceConverter,
        ViewToProjectionMatrix& viewToProjectionMatrix,
        PanelConfigurator& panelConfigurator,
        HudProvider& hudProvider) noexcept
        : TogglableFeature<SoundVisualizationFeature<PanelsType, SoundType>>{state.enabled}
        , state{state}
        , hookDependencies{hookDependencies}
        , viewRenderHook{viewRenderHook}
        , soundWatcher{soundWatcher}
        , hudInWorldPanelContainer{hudInWorldPanelContainer}
        , worldtoClipSpaceConverter{worldtoClipSpaceConverter}
        , viewToProjectionMatrix{viewToProjectionMatrix}
        , panelConfigurator{panelConfigurator}
        , hudProvider{hudProvider}
    {}

    void run() noexcept override {
        if (!isEnabled())
            return;

        constexpr auto kCrucialDependencies{HookDependenciesMask{}.set<PanoramaTransformFactory>().set<CurTime>()};
        if (!hookDependencies.requestDependencies(kCrucialDependencies))
            return;

        if (!worldtoClipSpaceConverter)
            return;

        const auto containerPanel{hudInWorldPanelContainer.get(hudProvider, panelConfigurator)};
        if (!containerPanel)
            return;

        const auto containerPanelChildren{containerPanel.children()};
        if (!containerPanelChildren)
            return;

        const HudInWorldPanels panels{*containerPanelChildren};

        if (state.containerPanelHandle != PanoramaUiEngine::getPanelHandle(containerPanel)) {
            state.panelIndices.clear();
            state.containerPanelHandle = PanoramaUiEngine::getPanelHandle(containerPanel);
        }

        std::size_t currentIndex = 0;
        for (const auto& sound : soundWatcher.getSoundsOfType<SoundType>()) {
            const auto soundInClipSpace = worldtoClipSpaceConverter.toClipSpace(sound.origin);
            if (!soundInClipSpace.onScreen())
                continue;

            const auto opacity = SoundVisualization<SoundType>::getOpacity(sound.getTimeAlive(hookDependencies.getDependency<CurTime>()));
            if (opacity <= 0.0f)
                continue;

            const auto panel = getPanel(containerPanel, panels, currentIndex);
            if (!panel)
                continue;

            const auto style = panel.getStyle();
            if (!style)
                continue;

            const auto styleSetter{panelConfigurator.panelStyle(*style)};
            styleSetter.setOpacity(opacity);
            styleSetter.setZIndex(-soundInClipSpace.z);

            const auto deviceCoordinates = soundInClipSpace.toNormalizedDeviceCoordinates();

            const auto& transformFactory = hookDependencies.getDependency<PanoramaTransformFactory>();
            PanoramaTransformations{
                transformFactory.scale(SoundVisualization<SoundType>::getScale(soundInClipSpace.z, viewToProjectionMatrix.getFovScale())),
                transformFactory.translate(deviceCoordinates.getX(), deviceCoordinates.getY())
            }.applyTo(styleSetter);

            ++currentIndex;
        }

        hideRemainingPanels(panels, currentIndex);
    }

private:
    friend TogglableFeature<SoundVisualizationFeature<PanelsType, SoundType>>;

    void onEnable() noexcept override {
        viewRenderHook.incrementReferenceCount();
        soundWatcher.startWatching<SoundType>();
    }

    void onDisable() noexcept override {
        viewRenderHook.decrementReferenceCount();
        soundWatcher.stopWatching<SoundType>();
        if (const auto containerPanel{hudInWorldPanelContainer.get(hudProvider, panelConfigurator)}) {
            if (const auto containerPanelChildren{containerPanel.children()})
                hideRemainingPanels(HudInWorldPanels{*containerPanelChildren}, 0);
        }
    }

    [[nodiscard]] auto getPanel(PanoramaUiPanel containerPanel, HudInWorldPanels inWorldPanels, std::size_t index) const noexcept -> PanoramaUiPanel {
        if (index < state.panelIndices.size()) {
            if (const auto panel{inWorldPanels.getPanel(state.panelIndices[index])})
                return panel;
            state.panelIndices.erase(state.panelIndices.begin() + index);
        }
        if (const auto panel{SoundVisualizationPanelFactory{*static_cast<cs2::CUIPanel*>(containerPanel), panelConfigurator}.createSoundVisualizationPanel(PanelsType::soundVisualizationPanelProperties())}) {
            state.panelIndices.push_back(inWorldPanels.getIndexOfLastPanel());
            return panel;
        }
        return PanoramaUiPanel{nullptr};
    }

    void hideRemainingPanels(HudInWorldPanels inWorldPanels, std::size_t firstIndexToHide) const noexcept {
        for (std::size_t i = firstIndexToHide; i < state.panelIndices.size(); ++i) {
            if (const auto panel{inWorldPanels.getPanel(state.panelIndices[i])}) {
                if (const auto style{panel.getStyle()})
                    panelConfigurator.panelStyle(*style).setOpacity(0.0f);
            }
        }
    }

    SoundVisualizationFeatureState& state;
    HookDependencies& hookDependencies;
    ViewRenderHook& viewRenderHook;
    SoundWatcher<SoundType>& soundWatcher;
    HudInWorldPanelContainer& hudInWorldPanelContainer;
    WorldToClipSpaceConverter& worldtoClipSpaceConverter;
    ViewToProjectionMatrix& viewToProjectionMatrix;
    PanelConfigurator& panelConfigurator;
    HudProvider& hudProvider;
};
