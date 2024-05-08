#pragma once

#include <cassert>
#include <memory>
#include <string>

#include <CS2/Classes/Panorama.h>
#include <CS2/Constants/ColorConstants.h>
#include <GameClasses/Panel.h>
#include <GameClasses/PanoramaUiPanel.h>
#include <GameEngine/PanelConfigurator.h>
#include "SoundVisualizationPanelProperties.h"

class SoundVisualizationPanelFactory {
public:
    SoundVisualizationPanelFactory(cs2::CUIPanel& parentPanel, PanelConfigurator panelConfigurator = PanelConfigurator{})
        : parentPanel{parentPanel}, panelConfigurator{std::move(panelConfigurator)}
    {
    }

    std::unique_ptr<PanoramaUiPanel> createSoundVisualizationPanel(const SoundVisualizationPanelProperties& properties) const
    {
        auto containerPanel = std::unique_ptr<cs2::CUIPanel>{Panel::create("", &parentPanel)};
        if (!containerPanel) {
            // Log an error message
            return nullptr;
        }

        if (const auto style{PanoramaUiPanel{containerPanel->uiPanel}.getStyle()}) {
            const auto styler = panelConfigurator.panelStyle(*style);
            styler.setWidth(cs2::CUILength::pixels(kWidth));
            styler.setHeight(cs2::CUILength::pixels(kHeight));
            if (properties.position == SoundVisualizationPosition::AboveOrigin) {
                styler.setPosition(cs2::CUILength::pixels(-kWidth * 0.5f), cs2::CUILength::pixels(-kHeight));
                styler.setTransformOrigin(cs2::CUILength::percent(50), cs2::CUILength::percent(100));
            } else {
                assert(properties.position == SoundVisualizationPosition::AtOrigin);
                styler.setPosition(cs2::CUILength::pixels(-kWidth * 0.5f), cs2::CUILength::pixels(-kHeight * 0.5f));
            }
        }

        applyStyleToImagePanel(PanoramaImagePanel::create("", containerPanel->uiPanel), properties);
        return std::make_unique<PanoramaUiPanel>(containerPanel->uiPanel);
    }

private:
    void applyStyleToImagePanel(cs2::CImagePanel* imagePanel, const SoundVisualizationPanelProperties& properties) const
    {
        if (!imagePanel) {
            return;
        }

        PanoramaImagePanel{imagePanel}.setImageSvg(properties.svgImagePath, properties.svgTextureHeight);
        if (const auto style{PanoramaUiPanel{imagePanel->uiPanel}.getStyle()}) {
            const auto styler = panelConfigurator.panelStyle(*style);
            styler.setAlign(cs2::k_EHorizontalAlignmentCenter, imageVerticalAlignment(properties.position));
            styler.setImageShadow(imageShadowParams());
        }
    }

    static PanelShadowParams imageShadowParams()
    {
        return PanelShadowParams{
            .horizontalOffset{cs2::CUILength::pixels(0)},
            .verticalOffset{cs2::CUILength::pixels(0)},
            .blurRadius{cs2::CUILength::pixels(1)},
            .strength = 3,
            .color{cs2::kColorBlack}
        };
    }

    static cs2::EVerticalAlignment imageVerticalAlignment(SoundVisualizationPosition position)
    {
        if (position == SoundVisualizationPosition::AboveOrigin) {
            return cs2::k_EVerticalAlignmentBottom;
        }
        return cs2::k_EVerticalAlignmentCenter;
    }

    static constexpr auto kWidth{256};
    static constexpr auto kHeight{256};

    cs2::CUIPanel& parentPanel;
    PanelConfigurator panelConfigurator;
};
