#pragma once

#include <algorithm>
#include <cassert>
#include <string_view>

#include <CS2/Constants/SoundNames.h>

struct WeaponReloadSound {
    /// The time at which the reload sound starts fading away.
    static constexpr float kFadeAwayStart = 1.8f;

    /// The duration of the reload sound fade-away effect.
    static constexpr float kFadeAwayDuration = 0.8f;

    /// The minimum scale factor for the reload sound.
    static constexpr float kMinScale = 0.5f;

    /// Returns true if the given sound name is a weapon reload sound, and false otherwise.
    static constexpr bool isSound(std::string_view soundName) noexcept {
        assert(!soundName.empty());
        return soundName.starts_with(cs2::kWeaponSoundsPath) &&
               (soundName.ends_with(cs2::kClipOutSoundSuffix) || soundName.ends_with(cs2::kCoverUpSoundSuffix));
    }
};
