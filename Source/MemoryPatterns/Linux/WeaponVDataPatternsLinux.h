#pragma once

#include <MemoryPatterns/WeaponVDataPatterns.h>
#include <MemorySearch/BytePatternLiteral.h>

inline OffsetToWeaponName WeaponVDataPatterns::getWeaponNameOffset() const noexcept
{
    // Search for the pattern with a maximum match distance of 16 bytes
    constexpr int maxMatchDistance = 16;
    auto patternResult = clientPatternFinder("74 ? 48 8B ? ? ? ? ? 48 8D ? ? ? ? ? BE ? ? ? ? 8B 3D ? ? ? ? 48 8D"_pat, maxMatchDistance);

    // If the pattern was not found, return a default offset value of 0
    if (!patternResult) {
        return OffsetToWeaponName(0);
    }

    // Move the read position to the next byte after the pattern match
    patternResult->add(5);

    // Read the offset value from memory
    return patternResult->readOffset<OffsetToWeaponName>();
}

