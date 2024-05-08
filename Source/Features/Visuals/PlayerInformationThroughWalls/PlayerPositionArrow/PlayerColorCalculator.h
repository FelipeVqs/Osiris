#pragma once

#include <utility>
#include <vector>

#include <CS2/Classes/Color.h>
#include <CS2/Classes/Entities/CCSPlayerController.h>
#include <CS2/Constants/ColorConstants.h>

/**
 * A template class for calculating the color of a player based on their teammate color index.
 * @tparam PlayerColorIndexAccessor A type that can access the teammate color index of a player.
 */
template <typename PlayerColorIndexAccessor>
struct PlayerColorCalculator {
    PlayerColorIndexAccessor playerColorIndexAccessor;

    /**
     * Gets the color of the player with the given teammate color index.
     * @param color A pointer to a cs2::Color object to store the player's color.
     * @return True if the player's color was successfully retrieved, false otherwise.
     */
    [[nodiscard]] bool getPlayerColor(cs2::Color* color) const {
        return getPlayerColor(playerColorIndexAccessor.getPlayerColorIndex(), color);
    }

private:
    /**
     * Gets the color of the player with the given teammate color index.
     * @param playerColorIndex The teammate color index of the player.
     * @param color A pointer to a cs2::Color object to store the player's color.
     * @return True if the player's color was successfully retrieved, false otherwise.
     */
    [[nodiscard]] bool getPlayerColor(cs2::CCSPlayerController::m_iCompTeammateColor playerColorIndex, cs2::Color* color) const {
        if (playerColorIndex >= 0 && playerColorIndex < cs2::kPlayerColors.size()) {
            *color = cs2::kPlayerColors[playerColorIndex];
            return true;
        }
        return false;
    }
};

/**
 * A constructor template alias for creating PlayerColorCalculator objects.
 * @tparam PlayerColorIndexAccessor A type that can access the teammate color index of a player.
 */
template <typename PlayerColorIndexAccessor>
PlayerColorCalculator(PlayerColorIndexAccessor) -> PlayerColorCalculator<PlayerColorIndexAccessor>;
