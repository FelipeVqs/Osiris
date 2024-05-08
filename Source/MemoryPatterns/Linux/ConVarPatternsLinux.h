#pragma once

#include <MemoryPatterns/ConVarPatterns.h>
#include <MemorySearch/BytePatternLiteral.h>
#include <optional>
#include <array>

constexpr OffsetToConVarValueType ConVarPatterns::offsetToConVarValueType() const noexcept
{
    // The pattern for finding the offset to the ConVarValueType.
    constexpr std::array<std::byte, 6> pattern1 = { 0x66, 0x41, 0x89, 0x46, 0x00, 0x66 };

    // Try to find the pattern in memory.
    auto match1 = tier0PatternFinder(pattern1);
    if (!match1) {
        return std::nullopt;
    }

    // Calculate the offset relative to the start of the pattern.
    return OffsetToConVarValueType(match1.value().getAddress() + match1.value().getPatternLength() + 4);
}

constexpr OffsetToConVarValue ConVarPatterns::offsetToConVarValue() const noexcept
{
    // The pattern for finding the offset to the ConVarValue.
    constexpr std::array<std::byte, 7> pattern2 = { 0x31, 0xF6, 0x48, 0x8D, 0x78, 0x00, 0x48 };

    // Try to find the pattern in memory.
    auto match2 = tier0PatternFinder(pattern2);
    if (!match2) {
        return std::nullopt;
    }

    // Calculate the offset relative to the start of the pattern.
    return OffsetToConVarValue(match2.value().getAddress() + match2.value().getPatternLength() + 5);
}

