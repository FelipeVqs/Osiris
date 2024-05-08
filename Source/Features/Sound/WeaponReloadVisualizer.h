#pragma once

#include <CS2/Classes/Panorama.h>
#include "Details/SoundVisualizationFeature.h"
#include "Details/SoundVisualizationPanelProperties.h"

// Add a forward declaration to avoid including the entire header
enum class WeaponReloadSound;

struct WeaponReloadPanels {
    [[nodiscard]] static inline SoundVisualizationPanelProperties soundVisualizationPanelProperties() noexcept
    {
        return SoundVisualizationPanelProperties{
            .svgImagePath = "s2r://panorama/images/icons/ui/switch_teams_dead.svg",
            .position = SoundVisualizationPosition::AtOrigin};
    }
};

// Add a constructor to allow for customization of the sound visualization
template<typename Panels, typename Sound>
struct SoundVisualizationFeature {
    SoundVisualizationFeature()
    {
        // Initialize the sound visualization with the given panels and sound
    }
};

// Add a static_assert to ensure that the WeaponReloadSound enum is defined
template<>
struct SoundVisualizationFeature<WeaponReloadPanels, WeaponReloadSound> {
    SoundVisualizationFeature()
    {
        static_assert(sizeof(WeaponReloadSound) > 0, "WeaponReloadSound not defined");
        // Initialize the sound visualization with the given panels and sound
    }
};

using WeaponReloadVisualizer = SoundVisualizationFeature<WeaponReloadPanels, WeaponReloadSound>;

