#pragma once

#include <algorithm>
#include <cstddef>
#include <concepts>
#include <ranges>
#include <span>

template <std::size_t Size, typename T>
concept ContiguousRange = std::ranges::contiguous_range<T> && requires { typename T::value_type; };

template <std::size_t Size, typename T>
class SpanSlice {
public:
    SpanSlice(T span, std::size_t centerOffset) noexcept
        requires ContiguousRange<T>
        : span{ span }, centerOffset{ centerOffset }
    {
        static_assert(Size != 0, "Size must be greater than zero.");
        if constexpr (Size > span.size()) {
            throw std::runtime_error("Span must have at least Size elements.");
        }
    }

    [[nodiscard]] const std::span<typename T::value_type> operator()() const noexcept
    {
        return span.subspan(getSliceStartOffset(), getSliceSize());
    }

private:
    [[nodiscard]] constexpr std::size_t getSliceSize() const noexcept
    {
        return std::min(span.size(), Size);
    }

    [[nodiscard]] constexpr std::size_t getSliceStartOffset() const noexcept
    {
        if (centerOffset < getSliceSize() / 2)
            return 0;
        if (centerOffset > span.size() - getSliceSize() / 2)
            return span.size() - getSliceSize();
        return centerOffset - getSliceSize() / 2;
    }

    T span;
    std::size_t centerOffset;
};
