#pragma once

#include "Hud/States/HudFeaturesStates.h"
#include "Sound/States/SoundFeaturesStates.h"
#include "Visuals/States/VisualFeaturesStates.h"

namespace {

class FeaturesStates {
public:
    HudFeaturesStates hudFeaturesStates;
    SoundFeaturesStates soundFeaturesStates;
    VisualFeaturesStates visualFeaturesStates;
};

} // namespace
