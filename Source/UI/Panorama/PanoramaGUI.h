#pragma once

#include <CS2/Classes/Panorama.h>
#include <FeatureHelpers/MainMenuProvider.h>
#include <MemoryPatterns/ClientPatterns.h>
#include <string_view>
#include <Utils/StringParser.h>
#include <Helpers/UnloadFlag.h>
#include <FeatureHelpers/TogglableFeature.h>

#include "PanoramaCommandDispatcher.h"

class PanoramaGUI {
public:
    void init(MainMenuProvider mainMenuProvider) noexcept {
        const auto mainMenu = mainMenuProvider.getMainMenuPanel();
        if (!mainMenu) {
            return;
        }

        // Ensure settings tab is loaded
        if (!ensureSettingsTabLoaded(mainMenu)) {
            return;
        }

        const auto settings = mainMenu.findChildInLayoutFile("JsSettings");
        if (settings) {
            settingsPanelPtr_ = settings;
        }

        createGUI(mainMenu);

        const auto openMenuButton = createOpenMenuButton(mainMenu);
        if (openMenuButton) {
            guiButtonPointer_ = openMenuButton;
        }

        const auto guiPanel = mainMenu.findChildInLayoutFile("OsirisMenuTab");
        if (guiPanel) {
            guiPanelPointer_ = guiPanel;
        }
    }

    ~PanoramaGUI() noexcept override {
        if (guiButtonPointer_.getHandle().isValid()) {
            PanoramaUiEngine::onDeletePanel(guiButtonPointer_.getHandle());
        }

        if (guiPanelPointer_.getHandle().isValid()) {
            PanoramaUiEngine::onDeletePanel(guiPanelPointer_.getHandle());
        }

        if (const auto settingsPanel = settingsPanelPtr_.get()) {
            PanoramaUiEngine::runScript(settingsPanel, "delete $.Osiris", "", 0);
        }
    }

    void run(Features features, UnloadFlag& unloadFlag) const noexcept {
        const auto guiPanel = guiPanelPointer_.get();
        if (!guiPanel) {
            return;
        }

        const auto cmdSymbol = PanoramaUiEngine::makeSymbol(0, "cmd");
        const auto cmd = guiPanel.getAttributeString(cmdSymbol, "");
        PanoramaCommandDispatcher{cmd, features, unloadFlag}();
        guiPanel.setAttributeString(cmdSymbol, "");
    }

private:
    bool ensureSettingsTabLoaded(const PanoramaPanel& mainMenu) const noexcept {
        // Ensure settings tab is loaded because we use CSS classes from settings
        // TODO: replace use of settings CSS classes with raw style properties
        return PanoramaUiEngine::runScript(mainMenu, "if (!$('#JsSettings')) MainMenu.NavigateToTab('JsSettings', 'settings/settings');", "", 0);
    }

    void createGUI(const PanoramaPanel& mainMenu) const noexcept {
        const auto settings = mainMenu.findChildInLayoutFile("JsSettings");
        if (!settings) {
            return;
        }

        PanoramaUiEngine::runScript(settings, R"(
            (function () {
                // ...
            })();
        )", "", 0);
    }

    PanoramaPanelPointer createOpenMenuButton(const PanoramaPanel& parent) const noexcept {
        if (!parent) {
            return {};
        }

        const auto mainMenuNavBarSettings = parent.FindChildTraverse("MainMenuNavBarSettings");
        if (!mainMenuNavBarSettings) {
            return {};
        }

        const auto openMenuButton = $.CreatePanel('RadioButton', mainMenuNavBarSettings.GetParent(), 'OsirisOpenMenuButton', {
            class: "mainmenu-top-navbar__radio-iconbtn",
            group: "NavBar",
            onactivate: "MainMenu.NavigateToTab('OsirisMenuTab', '');"
        });

        $.CreatePanel('Image', openMenuButton, '', {
            class: "mainmenu-top-navbar__radio-btn__icon",
            src: "s2r://panorama/images/icons/ui/bug.vsvg"
        });

        return openMenuButton;
    }

    PanoramaPanelPointer guiPanelPointer_;
    PanoramaPanelPointer guiButtonPointer_;
    PanoramaPanelPointer settingsPanelPtr_;
};
