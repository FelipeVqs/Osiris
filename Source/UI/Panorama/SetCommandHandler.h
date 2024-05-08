#pragma once

#include <Features/Features.h>
#include <FeatureHelpers/TogglableFeature.h>
#include <Utils/StringParser.h>
#include <map>
#include <cctype>

struct SetCommandHandler {
    SetCommandHandler(StringParser& parser, Features features) noexcept
        : parser{parser}
        , features{std::move(features)}
    {
    }

    void operator()() noexcept
    {
        const auto section = parser.getLine('/');
        if (handlers.count(section)) {
            handlers[section](parser.getLine('/'));
        }
    }

private:
    void handleHudSection(const std::string& feature) const noexcept
    {
        handleFeature(features.hudFeatures().bombTimer(), feature, 'b');
        handleFeature(features.hudFeatures().defusingAlert(), feature, 'd');
        handleFeature(features.hudFeatures().killfeedPreserver(), feature, 'p');
    }

    void handleSoundSection(const std::string& feature) const noexcept
    {
        handleTogglableFeature(features.soundFeatures().footstepVisualizer(), feature, 'f');
        handleTogglableFeature(features.soundFeatures().bombPlantVisualizer(), feature, 'b');
        handleTogglableFeature(features.soundFeatures().bombBeepVisualizer(), feature, 'e');
        handleTogglableFeature(features.soundFeatures().bombDefuseVisualizer(), feature, 'D');
        handleTogglableFeature(features.soundFeatures().weaponScopeVisualizer(), feature, 's');
        handleTogglableFeature(features.soundFeatures().weaponReloadVisualizer(), feature, 'r');
    }

    void handleVisualsSection(const std::string& feature) const noexcept
    {
        handleFeature(features.visualFeatures().playerInformationThroughWalls(), feature, 'w');
        handleTogglableFeature(features.visualFeatures().playerPositionToggle(), feature, 'W');
        handleFeature(features.visualFeatures().playerPositionArrowColorToggle(), feature, 'c');
        handleTogglableFeature(features.visualFeatures().playerHealthToggle(), feature, 'h');
        handleFeature(features.visualFeatures().playerHealthTextColorToggle(), feature, 'H');
        handleTogglableFeature(features.visualFeatures().playerActiveWeaponToggle(), feature, 'a');
        handleFeature(features.visualFeatures().playerDefuseIconToggle(), feature, 'i');
        handleFeature(features.visualFeatures().hostagePickupIconToggle(), feature, 't');
    }

    template <typename Feature, typename = std::enable_if_t<std::is_base_of_v<Feature, TogglableFeature<Feature>>>>
    void handleTogglableFeature(Feature&& feature, const std::string&, char) const noexcept
    {
        if (parser.getChar() == '1') {
            feature.disable();
        } else if (parser.getChar() == '0') {
            feature.enable();
        }
    }

    template <typename Feature>
    void handleFeature(Feature&& feature, const std::string& param, char flag) const noexcept
    {
        if (param[0] == flag) {
            feature.update(param[1]);
        }
    }

    StringParser& parser;
    Features features;

    std::map<std::string, void (SetCommandHandler::*)(const std::string&)> handlers = {
        {"hud", &SetCommandHandler::handleHudSection},
        {"visuals", &SetCommandHandler::handleVisualsSection},
        {"sound", &SetCommandHandler::handleSoundSection},
    };
};
