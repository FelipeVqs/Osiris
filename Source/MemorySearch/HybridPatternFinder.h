#pragma once

#include <cstddef>
#include <span>
#include <string_view>

#include <Platform/Macros/FunctionAttributes.h>

#include "BytePattern.h"
#include "PatternFinderScalar.h"
#include "PatternFinderSIMD.h"

class HybridPatternFinder final {
public:
    constexpr HybridPatternFinder(std::span<const std::byte> bytes, BytePattern pattern) noexcept
        : bytes{ bytes }, pattern{ pattern }
    {
    }

    [[nodiscard]] const std::byte* findNextOccurrence() const noexcept
    {
        PatternFinderSIMD simdFinder{bytes, pattern};
        if (const auto foundSIMD = simdFinder(); foundSIMD != nullptr) {
            updateRemainingBytes(foundSIMD);
            return foundSIMD;
        }

        if (const auto foundScalar{PatternFinderScalar{simdFinder.getNotCheckedBytes(), pattern}.find()}; foundScalar != nullptr) {
            updateRemainingBytes(foundScalar);
            return foundScalar;
        }

        return nullptr;
    }

private:
    void updateRemainingBytes(const std::byte* foundPosition) noexcept
    {
        bytes = {foundPosition + 1, bytes.data() + bytes.size()};
    }

    std::span<const std::byte> bytes;
    BytePattern pattern;
};

class PatternFinderScalar final {
public:
    constexpr PatternFinderScalar(std::span<const std::byte> bytes, BytePattern pattern) noexcept
        : bytes{ bytes }, pattern{ pattern }
    {
    }

    [[nodiscard]] const std::byte* find() const noexcept
    {
        // Implementation goes here
    }

    [[nodiscard]] std::span<const std::byte> getNotCheckedBytes() const noexcept
    {
        // Implementation goes here
    }

private:
    std::span<const std::byte> bytes;
    BytePattern pattern;
};
