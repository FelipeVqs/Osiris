#pragma once

#include <GameClasses/OffsetTypes/WeaponServicesOffset.h>
#include <Helpers/PatternNotFoundLogger.h>
#include <MemorySearch/PatternFinder.h>

struct WeaponServicesPatterns {
    WeaponServicesPatterns(const PatternFinder<PatternNotFoundLogger>& clientPatternFinder) noexcept
        : clientPatternFinder(clientPatternFinder) {}

    [[nodiscard]] OffsetToActiveWeapon offsetToActiveWeapon() const noexcept;

    const PatternFinder<PatternNotFoundLogger>& clientPatternFinder;
};

// Implementation of the member function
OffsetToActiveWeapon WeaponServicesPatterns::offsetToActiveWeapon() const noexcept {
    // Implementation using clientPatternFinder to find the offset
    // ...
}
