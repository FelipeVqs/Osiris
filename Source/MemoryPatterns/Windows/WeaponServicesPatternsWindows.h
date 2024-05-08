#pragma once

#include <MemoryPatterns/WeaponServicesPatterns.h>
#include <MemorySearch/BytePatternLiteral.h>

inline OffsetToActiveWeapon WeaponServicesPatterns::getActiveWeaponOffset() const noexcept {
    const auto patternResult = findClientPattern("? FF FF FF FF 48 85 D2 75 ? ? 8B"_pat);
    if (!patternResult.found) {
        // Handle error, e.g. log an error message
        return OffsetToActiveWeapon{};
    }
    return patternResult.readOffset<OffsetToActiveWeapon>();
}
