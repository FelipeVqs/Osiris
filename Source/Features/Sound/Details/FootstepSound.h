#pragma once

#include <algorithm>
#include <cassert>
#include <string_view>

#include <CS2/Constants/SoundNames.h>

namespace cs2 {
using StringView = std::string_view;
}

struct FootstepSound {
    static constexpr auto kFadeAwayStart = 1.6f;
    static constexpr auto kFadeAwayDuration = 0.4f;
    static constexpr auto kMinScale = 0.3f;

    static_assert(kFadeAwayStart > kFadeAwayDuration, "kFadeAwayStart must be greater than kFadeAwayDuration");

    [[nodiscard]] static constexpr bool isSound(StringView soundName) noexcept
    {
        constexpr auto footstepSoundsPath = cs2::kPlayerFootstepSoundsPath;
        constexpr auto suitSoundsPrefix = cs2::kPlayerSuitSoundPrefix;

        if (soundName.starts_with(footstepSoundsPath)) {
            return !soundName.substr(footstepSoundsPath.length()).starts_with(suitSoundsPrefix);
        }
        return false;
    }
};
