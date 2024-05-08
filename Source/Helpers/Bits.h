#pragma once

#include <cassert>
#include <cstdint>
#include <concepts>
#include <type_traits>

#include <Platform/Macros/IsPlatform.h>

#if IS_WIN64()
#include <intrin.h>
#endif

namespace bits
{

[[nodiscard]] inline int countrZero(unsigned int x) noexcept
{
    assert(x != 0 && "x must be non-zero");
#if IS_WIN64()
    unsigned long result;
    _BitScanForward(&result, x);
    return static_cast<int>(result);
#elif IS_LINUX()
    return __builtin_ctz(x);
#endif
}

[[nodiscard]] inline int countrZero(unsigned long long x) noexcept
{
    assert(x != 0 && "x must be non-zero");
#if IS_WIN64()
    unsigned long long result;
    _BitScanForward64(&result, x);
    return static_cast<int>(result);
#elif IS_LINUX()
    return __builtin_ctzll(x);
#endif
}

template <typename T>
concept UnsignedIntegral = std::unsigned_integral<T>;

template <UnsignedIntegral T>
[[nodiscard]] constexpr T clearRightmostSetBit(T value) noexcept
{
    static_assert(std::is_same_v<T, std::uint8_t> || std::is_same_v<T, std::uint16_t> ||
                  std::is_same_v<T, std::uint32_t> || std::is_same_v<T, std::uint64_t>,
                  "Unsupported type. Only uint8_t, uint16_t, uint32_t, and uint64_t are supported.");

    return value & (value - 1);
}

template <>
[[nodiscard]] constexpr std::uint64_t clearRightmostSetBit<std::uint64_t>(std::uint64_t value) noexcept
{
    return value & (value - 1);
}

template <UnsignedIntegral T>
[[nodiscard]] constexpr T clearRightmostSetBit(T value, std::true_type) noexcept
{
    return value & (value - 1);
}

template <UnsignedIntegral T>
[[nodiscard]] constexpr T clearRightmostSetBit(T value, std::false_type) noexcept
{
    using U = std::make_unsigned_t<std::underlying_type_t<T>>;
    return static_cast<T>(clearRightmostSetBit(static_cast<U>(value)));
}

template <UnsignedIntegral T>
[[nodiscard]] constexpr T clearRightmostSetBit(T value) noexcept
{
    return clearRightmostSetBit(value, std::bool_constant<(sizeof(T) <= sizeof(std::uint64_t))>{});
}

} // namespace bits
