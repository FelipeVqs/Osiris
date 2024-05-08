#pragma once

#ifdef __cpp_lib_span
#include <span>
#else
#include <span> // In case of C++20
#endif

#include <string_view>

#include "BytePattern.h"

class PatternFinderScalar {
public:
    PatternFinderScalar(std::span<const std::byte> bytes, BytePattern pattern) noexcept
        : bytes{ bytes }, pattern{ pattern }, currentPos{ 0 }
    {
    }

    const std::byte* find() const noexcept
    {
        while (remainingBytes() >= pattern.length()) {
            if (pattern.matches(bytes.subspan(currentPos, pattern.length())))
                return &bytes[currentPos];
            ++currentPos;
        }
        return nullptr;
    }

private:
    [[nodiscard]] std::size_t remainingBytes() const noexcept
    {
        return bytes.size() - currentPos;
    }

    std::size_t currentPos;
    std::span<const std::byte> bytes;
    BytePattern pattern;
};
