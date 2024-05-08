#pragma once

#include <algorithm>

template <typename SoundType>
struct SoundVisualization {
    /// Struct for visualizing sounds.

    /// Returns the scale factor for the sound at the given distance and field of view scale.
    [[nodiscard]] static constexpr float getScale(float z, float fovScale) noexcept {
        static_assert(
            std::is_same_v<float, SoundType::DistanceType> &&
            std::is_same_v<float, SoundType::FovScaleType>,
            "SoundType must have DistanceType and FovScaleType as float"
        );

        constexpr auto kMaxScale{ 1.0f };
        const auto inverseDistance = z / fovScale;
        const auto clampedValue = std::clamp(500.0f / (inverseDistance + 400.0f), SoundType::kMinScale, kMaxScale);
        return clampedValue;
    }

    /// Returns the opacity of the sound based on its age.
    [[nodiscard]] static constexpr float getOpacity(float timeAlive) noexcept {
        static_assert(std::is_same_v<float, SoundType::TimeType>, "SoundType must have TimeType as float");

        if (timeAlive >= SoundType::kFadeAwayStart) {
            const auto fadeAwayProgress = (timeAlive - SoundType::kFadeAwayStart) / SoundType::kFadeAwayDuration;
            return 1.0f - std::min(fadeAwayProgress, 1.0f);
        } else {
            return 1.0f;
        }
    }
};
