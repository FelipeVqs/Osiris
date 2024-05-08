#pragma once

#include <FeatureHelpers/FeatureHelpers.h>
#include "PlayerInformationThroughWalls/PlayerInformationThroughWalls.h"
#include "VisualFeaturesStates.h"

class LoopModeGameHook;

struct VisualFeatures {
    // Prevents instantiation of the class from outside.
    VisualFeatures(const VisualFeatures&) = delete;
    VisualFeatures& operator=(const VisualFeatures&) = delete;

    // Returns a new instance of the VisualFeatures class.
    static VisualFeatures create(VisualFeaturesStates& states, FeatureHelpers& helpers, ViewRenderHook& viewRenderHook) noexcept;

    [[nodiscard]] PlayerInformationThroughWallsToggle playerInformationThroughWalls() const noexcept
    {
        return PlayerInformationThroughWallsToggle{states.playerInformationThroughWallsState, helpers.hudInWorldPanelContainer, viewRenderHook, helpers.panelConfigurator(), helpers.hudProvider};
    }

    [[nodiscard]] PlayerPositionToggle playerPositionToggle() const noexcept
    {
        return PlayerPositionToggle{states.playerInformationThroughWallsState};
    }

    [[nodiscard]] PlayerPositionArrowColorToggle playerPositionArrowColorToggle() const noexcept
    {
        return PlayerPositionArrowColorToggle{states.playerInformationThroughWallsState.playerPositionArrowColor};
    }

    [[nodiscard]] PlayerHealthToggle playerHealthToggle() const noexcept
    {
        return PlayerHealthToggle{states.playerInformationThroughWallsState};
    }

    [[nodiscard]] PlayerHealthTextColorToggle playerHealthTextColorToggle() const noexcept
    {
        return PlayerHealthTextColorToggle{states.playerInformationThroughWallsState.playerHealthTextColor};
    }

    [[nodiscard]] PlayerActiveWeaponToggle playerActiveWeaponToggle() const noexcept
    {
        return PlayerActiveWeaponToggle{states.playerInformationThroughWallsState};
    }

    [[nodiscard]] PlayerDefuseIconToggle playerDefuseIconToggle() const noexcept
    {
        return PlayerDefuseIconToggle{states.playerInformationThroughWallsState.playerStateIconsToShow};
    }

    [[nodiscard]] HostagePickupIconToggle hostagePickupIconToggle() const noexcept
    {
        return HostagePickupIconToggle{states.playerInformationThroughWallsState.playerStateIconsToShow};
    }

    // The visual features states.
    VisualFeaturesStates& states;

    // The feature helpers.
    FeatureHelpers& helpers;

    // The view render hook.
    ViewRenderHook& viewRenderHook;
};

// Returns a new instance of the VisualFeatures class.
VisualFeatures VisualFeatures::create(VisualFeaturesStates& states, FeatureHelpers& helpers, ViewRenderHook& viewRenderHook) noexcept
{
    return VisualFeatures{states, helpers, viewRenderHook};
}
