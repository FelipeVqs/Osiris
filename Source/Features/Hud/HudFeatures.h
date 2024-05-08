#pragma once

#include <FeatureHelpers/FeatureHelpers.h>

#include "BombTimer.h"
#include "DefusingAlert.h"
#include "KillfeedPreserver.h"
#include "States/HudFeaturesStates.h"

struct HudFeatures {
    constexpr BombTimer bombTimer() const {
        return BombTimer{states.bombTimerState, hookDependencies, helpers.hudProvider};
    }

    constexpr DefusingAlert defusingAlert() const {
        return DefusingAlert{
            states.defusingAlertState,
            hookDependencies,
            helpers.hudProvider,
            helpers.panelConfigurator()
        };
    }

    constexpr KillfeedPreserver killfeedPreserver() const {
        return KillfeedPreserver{states.killfeedPreserverState, hookDependencies, helpers.hudProvider, helpers.gameRules};
    }

    HudFeaturesStates const& states;
    FeatureHelpers const& helpers;
    HookDependencies const& hookDependencies;
};
