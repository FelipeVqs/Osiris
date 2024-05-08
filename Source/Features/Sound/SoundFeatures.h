#pragma once

#include "BombBeepVisualizer.h"
#include "BombDefuseVisualizer.h"
#include "BombPlantVisualizer.h"
#include "FootstepVisualizer.h"
#include "SoundFeaturesStates.h"
#include "WeaponReloadVisualizer.h"
#include "WeaponScopeVisualizer.h"
#include <Hooks/ViewRenderHook.h>

struct SoundFeatures {
    [[nodiscard]] constexpr FootstepVisualizer footstepVisualizer() const noexcept
    {
        return createSoundVisualizationFeature<FootstepVisualizer>(states.footstepVisualizerState);
    }

    [[nodiscard]] constexpr BombPlantVisualizer bombPlantVisualizer() const noexcept
    {
        return createSoundVisualizationFeature<BombPlantVisualizer>(states.bombPlantVisualizerState);
    }

    [[nodiscard]] constexpr BombBeepVisualizer bombBeepVisualizer() const noexcept
    {
        return createSoundVisualizationFeature<BombBeepVisualizer>(states.bombBeepVisualizerState);
   
