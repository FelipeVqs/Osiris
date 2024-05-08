#pragma once

#include <GameClasses/Panel.h>
#include <GameClasses/PanoramaUiPanel.h>
#include <Helpers/HudProvider.h>
#include <Helpers/PanoramaPanelPointer.h>
#include "PanelConfigurator.h"

class HudInWorldPanelContainer {
public:
    HudInWorldPanelContainer() = default;
    HudInWorldPanelContainer(const HudInWorldPanelContainer&) = delete;
    HudInWorldPanelContainer(HudInWorldPanelContainer&&) = delete;
    HudInWorldPanelContainer& operator=(const HudInWorldPanelContainer&) = delete;
    HudInWorldPanelContainer& operator=(HudInWorldPanelContainer&&) = delete;

    ~HudInWorldPanelContainer() noexcept
    {
        if (containerPanel)
            PanoramaUiEngine::onDeletePanel(containerPanel->getHandle());
    }

    [[nodiscard]] const PanoramaUiPanel get(HudProvider hudProvider, const PanelConfigurator& panelConfigurator) const noexcept
    {
        if (containerPanel)
            return *containerPanel;
        return createPanel(hudProvider, panelConfigurator);
    }

private:
    [[nodiscard]] const PanoramaUiPanel createPanel(HudProvider hudProvider, const PanelConfigurator& panelConfigurator) const noexcept
    {
        if (const auto hudReticle = hudProvider.getHudReticle()) {
            if (const auto panel = Panel::create("", hudReticle)) {
                if (const auto style{PanoramaUiPanel{panel->uiPanel}.getStyle()})
                    panelConfigurator.panelStyle(*style).fitParent();
                std::unique_ptr<PanoramaUiPanel> newPanel{ panel->uiPanel };
                containerPanel.swap(newPanel);
                return *containerPanel;
            }
        }
        return PanoramaUiPanel{ nullptr };
    }

    std::unique_ptr<PanoramaUiPanel> containerPanel;
};
