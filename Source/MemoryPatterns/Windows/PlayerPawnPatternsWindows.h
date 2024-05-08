#pragma once

#include <MemoryPatterns/PlayerPawnPatterns.h>
#include <MemorySearch/BytePatternLiteral.h>

inline OffsetToPlayerPawnImmunity PlayerPawnPatterns::getPlayerPawnImmunityOffset() const noexcept
{
    const auto patternResult = clientPatternFinder("0F B6 83 ? ? ? ? 84 C0 75 ? 41"_pat);
    if (!patternResult)
    {
        // Handle error
        return {};
    }

    return patternResult.add(3).readOffset<OffsetToPlayerPawnImmunity>();
}

inline OffsetToWeaponServices PlayerPawnPatterns::getWeaponServicesOffset() const noexcept
{
    const auto patternResult = clientPatternFinder("48 8B 88 ? ? ? ? 48 8D 15 ? ? ? ? E8 ? ? ? ? 48"_pat);
    if (!patternResult)
    {
        // Handle error
        return {};
    }

    return patternResult.add(3).readOffset<OffsetToWeaponServices>();
}

inline OffsetToPlayerController PlayerPawnPatterns::getPlayerControllerOffset() const noexcept
{
    const auto patternResult = clientPatternFinder("8B 89 ? ? ? ? 4C 89 60"_pat);
    if (!patternResult)
    {
        // Handle error
        return {};
    }

    return patternResult.add(2).readOffset<OffsetToPlayerController>();
}

inline OffsetToIsDefusing PlayerPawnPatterns::getIsDefusingOffset() const noexcept
{
    const auto patternResult = clientPatternFinder("80 BF ? ? ? ? ? 0F 85 ? ? ? ? 80 BF ? ? ? ? ? 75"_pat);
    if (!patternResult)
    {
        // Handle error
        return {};

