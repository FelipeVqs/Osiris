#pragma once

#include <array>
#include <bit>
#include <cstddef>
#include <type_traits>

template <typename T, T Min, T Max>
struct InRange {
    static_assert(Min <= Max, "Min must be less than or equal to Max");

    explicit(false) constexpr InRange(T Value) noexcept
        : value{Value}
    {
        static_assert(Value >= Min && Value <= Max, "Value must be in the range [Min, Max]");
    }

    constexpr operator T() const noexcept
    {
        return value;
    }

    T value;
};
