#pragma once

#include <concepts>
#include <iostream>
#include <limits>
#include <type_traits>

template <typename Flag, typename StorageType = std::underlying_type_t<Flag>,
          typename = std::enable_if_t<std::is_enum_v<Flag>>>
class BitFlags {
public:
    constexpr BitFlags() noexcept = default;

    template <Flag flag>
    constexpr void set() noexcept
    {
        flags |= toMask<flag>();
    }

    template <Flag flag>
    constexpr void unset() noexcept
    {
        flags &= ~toMask<flag>();
    }

    template <Flag flag>
    [[nodiscard]] constexpr bool has() const noexcept
    {
        return (flags & toMask<flag>()) != 0;
    }

    [[nodiscard]] explicit constexpr operator bool() const noexcept
    {
        return flags != 0;
    }

    friend std::ostream& operator<<(std::ostream& os, const BitFlags& flags)
    {
        os << flags.flags;
        return os;
    }

private:
    static_assert(std::numeric_limits<StorageType>::digits >= std::numeric_limits<Flag>::max(),
                  "StorageType must have enough bits to represent all Flag values.");

    template <Flag flag>
    static constexpr StorageType toMask() noexcept
    {
        static_assert(static_cast<StorageType>(flag) >= 0);
        static_assert(static_cast<StorageType>(flag) < std::numeric_limits<StorageType>::digits);
        return 1 << static_cast<StorageType>(flag);
    }

    StorageType flags{0};
};
