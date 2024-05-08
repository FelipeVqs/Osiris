#pragma once

#include <CS2/Classes/Color.h>
#include <CS2/Constants/ColorConstants.h>
#include <FeatureHelpers/TeamNumber.h>

struct TeamColorCalculator {
    TeamColorCalculator(TeamNumber team_number) : teamNumber(team_number) {}

    [[nodiscard]] cs2::Color getTeamColor() const noexcept {
        switch (teamNumber) {
            case TeamNumber::TT: return cs2::kColorTeamTT;
            case TeamNumber::CT: return cs2::kColorTeamCT;
            default: return cs2::kColorWhite;
        }
    }

    TeamNumber teamNumber;
};

// Example usage:
// TeamColorCalculator calculator(TeamNumber::TT);
// cs2::Color team_color = calculator.getTeamColor();
