// aspect\_ratio.h

#pragma once

namespace cs2 {

/**
 * The default aspect ratio of a 4:3 aspect ratio.
 */
constexpr float kDefaultAspectRatio{4.0f / 3.0f};

/**
 * Calculates the width of a window given its height and the aspect ratio.
 *
 * @param height The height of the window.
 * @param aspectRatio The aspect ratio of the window.
 * @return The width of the window.
 */
float CalculateWidth(float height, float aspectRatio);

}  // namespace cs2


// aspect_ratio.cpp

#include "aspect_ratio.h"

namespace cs2 {

float CalculateWidth(float height, float aspectRatio) {
  return height * aspectRatio;
}

}  // namespace cs2
