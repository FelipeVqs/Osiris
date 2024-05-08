#pragma once

#include <algorithm>
#include <cassert>
#include <string_view>

#include <CS2/Constants/SoundNames.h>

struct BombPlantSound {
    static constexpr float kFadeAwayStart = 2.1f;
    static constexpr float kFadeAwayDuration = 0.4f;
    static constexpr float kMinScale = 0.4f;

    [[nodiscard]] static constexpr bool is_sound(std::string_view sound_name) noexcept {
        return sound_name == cs2::kBombPlantSoundPath;
    }
};
