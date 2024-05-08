#pragma once

#include <cassert>
#include <cmath> // for std::abs

#include "NormalizedDeviceCoordinates.h"

struct ClipSpaceCoordinates {
    [[nodiscard]] bool onScreen() const noexcept
    {
        return w >= 0.001f && std::abs(w) >= std::numeric_limits<float>::epsilon();
    }

    [[nodiscard]] NormalizedDeviceCoordinates toNormalizedDeviceCoordinates() const noexcept
    {
        if (!onScreen()) {
            return NormalizedDeviceCoordinates{ 0.f, 0.f };
        }
        const auto inverseW = 1.0f / w;
        return NormalizedDeviceCoordinates{ x * inverseW, y * inverseW };
    }

    float x;
    float y;
    float z;
    float w;
};
