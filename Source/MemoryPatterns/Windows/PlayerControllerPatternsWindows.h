#pragma once

#include <MemoryPatterns/PlayerControllerPatterns.h>
#include <MemorySearch/BytePatternLiteral.h>
#include <optional>

// Define the offset types as std::byte to be consistent with the memory library.
using OffsetToPlayerPawnHandle = std::byte;
using OffsetToPlayerColor = std::byte;

// Use constexpr instead of inline for the functions that don't modify the object state.
constexpr OffsetToPlayerPawnHandle PlayerControllerPatterns::offsetToPlayerPawnHandle() const noexcept
{
    // Use std::string_view instead of raw string literals for the pattern data.
    constexpr std::string_view pattern = "C1 48 85 C9 74 ? 8B 89 ? ? ? ?"_pat;

    // Use std::optional instead of returning a raw offset value, to indicate whether the pattern was found or not.
    const auto result = clientPatternFinder(pattern).add(8).template readOffset<OffsetToPlayerPawnHandle>();

    // Return the result if it's not empty, otherwise return a default-constructed offset value.
    return result.has_value() ? *result : OffsetToPlayerPawnHandle{};
}

// Use constexpr instead of inline for the functions that don't modify the object state.
constexpr OffsetToPlayerColor PlayerControllerPatterns::offsetToPlayerColor() const noexcept
{
    // Use std::string_view instead of raw string literals for the pattern data.
    constexpr std::string_view pattern = "E8 ? ? ? ? 84 C0 74 ? 41 8B ? ? ? ? ? EB"_pat;

    // Use std::optional instead of returning a raw offset value, to indicate whether the pattern was found or not.
    const auto result = clientPatternFinder(pattern).add(12).template readOffset<OffsetToPlayerColor>();

    // Return the result if it's not empty, otherwise return a default-constructed offset value.
    return result.has_value() ? *result : OffsetToPlayerColor{};
}

