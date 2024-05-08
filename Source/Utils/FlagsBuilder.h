#pragma once

#include <concepts>
#include <type_traits>
#include <utility>

template <std::integral T, typename Flag>
class FlagsBuilder {
public:
    constexpr FlagsBuilder(T flags = T{}) noexcept : flags(flags) {}

    template <Flag flag>
    constexpr FlagsBuilder& set(bool b) noexcept {
        static_assert(std::in_range<T>(rawType<flag>()));
        if (b)
            flags |= static_cast<T>(flag);
        return *this;
    }

    [[nodiscard]] T get() const noexcept {
        return flags;
    }

    constexpr FlagsBuilder& reset() noexcept {
        flags = T{};
        return *this;
    }

    template <Flag flag>
    constexpr bool isSet() const noexcept {
        return (flags & rawType<flag>()) != T{};
    }

private:
    template <Flag flag>
    static constexpr auto rawType() noexcept {
        if constexpr (std::is_enum_v<Flag>) {
            return static_cast<std::underlying_type_t<Flag>>(flag);
        } else {
            if constexpr (std::is_integral_v<Flag>) {
                return flag;
            } else {
                static_assert(!std::is_same_v<Flag, Flag>, "Unsupported Flag type");
            }
        }
    }

    T flags;
};
