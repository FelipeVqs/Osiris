#pragma once

#include <cassert>
#include <cstdint>

struct ToRvaConverter {
    // Constructor to initialize the base address
    ToRvaConverter(std::uintptr_t base) noexcept : baseAddress(base) {}

    // Convert a virtual address to a relative virtual address
    [[nodiscard]] constexpr std::uint32_t toRva(std::uintptr_t address) const noexcept
    {
        // Ensure that the input address is not less than the base address
        address = clamp(address, baseAddress, std::numeric_limits<std::uintptr_t>::max());

        // Calculate the relative virtual address
        return static_cast<std::uint32_t>(address - baseAddress);
    }

    // Helper function to clamp a value between two bounds
    template <typename T>
    constexpr T clamp(T value, T low, T high) noexcept
    {
        return value < low ? low : (value > high ? high : value);
    }

    std::uintptr_t baseAddress;
};
