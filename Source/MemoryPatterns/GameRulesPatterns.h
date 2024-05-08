#pragma once

#include <GameClasses/OffsetTypes/GameRulesOffset.h>
#include <Helpers/PatternNotFoundLogger.h>
#include <MemorySearch/PatternFinder.h>

struct GameRulesPatterns {
    GameRulesPatterns(const PatternFinder<PatternNotFoundLogger>& clientPatternFinder)
        : clientPatternFinder(clientPatternFinder) {}

    [[nodiscard]] GameRulesOffset::RoundStartTimeOffset roundStartTimeOffset() const noexcept;

    const PatternFinder<PatternNotFoundLogger>& clientPatternFinder;
};

GameRulesOffset::RoundStartTimeOffset GameRulesPatterns::roundStartTimeOffset() const noexcept {
    // Implement the calculation of the round start time offset here
    // using the clientPatternFinder object.
}
