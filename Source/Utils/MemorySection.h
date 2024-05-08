#pragma once

#include <cstddef>
#include <cstdint>
#include <span>

static_assert(sizeof(std::uintptr_t) >= sizeof(std::byte*), "std::uintptr_t is not large enough to hold a pointer to std::byte");

struct MemorySection {
    MemorySection() = default;

    explicit MemorySection(std::span<const std::byte> section) noexcept
        : base{reinterpret_cast<std::uintptr_t>(section.data())}
        , size{section.size()}
    {
    }

    [[nodiscard]] const std::span<const std::byte> raw() const noexcept
    {
        return {reinterpret_cast<const std::byte*>(base), size};
    }

    [[nodiscard]] constexpr bool contains(std::uintptr_t address, std::size_t objectSize) const noexcept requires(address <= std::numeric_limits<std::uintptr_t>::max())
    {
        return address >= base && size >= objectSize && (address - base) <= size - objectSize;
    }

    [[nodiscard]] constexpr bool contains(std::uintptr_t address) const noexcept requires(address <= std::numeric_limits<std::uintptr_t>::max())
    {
        return address >= base && address - base < size;
    }

    [[nodiscard]] std::size_t offsetOf(std::uintptr_t address) const noexcept requires(address <= std::numeric_limits<std::uintptr_t>::max())
    {
        assert(contains(address));
        return address - base;
    }

private:
    std::uintptr_t base{0};
    std::size_t size{0};
};
