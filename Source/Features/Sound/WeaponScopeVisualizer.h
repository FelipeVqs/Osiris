#pragma once

#include <CS2/Classes/Panorama.h>
#include "Details/SoundVisualizationFeature.h"
#include "Details/SoundVisualizationPanelProperties.h"

struct WeaponScopePanels {
    WeaponScopePanels(const std::string& svgImagePath, SoundVisualizationPosition position)
        : panelProperties{svgImagePath, position} {}

    SoundVisualizationPanelProperties panelProperties;
};

using WeaponScopeSound = void(); // not sure what this type should be

inline SoundVisualizationPanelProperties WeaponScopePanels::soundVisualizationPanelProperties() noexcept {
    return SoundVisualizationPanelProperties{
        .svgImagePath = "s2r://panorama/images/icons/ui/chatwheel_sniperspotted.svg",
        .position = SoundVisualizationPosition::AtOrigin};
}

using WeaponScopeVisualizer = SoundVisualizationFeature<WeaponScopePanels, WeaponScopeSound>;
