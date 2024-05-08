#pragma once

#include <algorithm>
#include <cassert>
#include <string_view>

#include <CS2/Constants/SoundNames.h>

struct WeaponScopeSound {
    static constexpr float kFadeAwayStart = 1.8f;
    static constexpr float kFadeAwayDuration = 0.8f;
    static constexpr float kMinScale = 0.5f;

    [[nodiscard]] static constexpr bool isSound(std::string_view soundName) noexcept {
        const std::string_view weapon_sounds_path = cs2::kWeaponSoundsPath;
        const std::string_view zoom_sound_name_part = cs2::kZoomSoundNamePart;

        return soundName.starts_with(weapon_sounds_path) &&
               soundName.find(zoom_sound_name_part) != std::string_view::npos;
    }
};
