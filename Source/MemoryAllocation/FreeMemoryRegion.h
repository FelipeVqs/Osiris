#pragma once

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <span>

class FreeMemoryRegion {
public:
    FreeMemoryRegion(const FreeMemoryRegion&) = delete;
    FreeMemoryRegion(FreeMemoryRegion&&) noexcept;
    FreeMemoryRegion& operator=(const FreeMemoryRegion&) = delete;
    FreeMemoryRegion& operator=(FreeMemoryRegion&&) noexcept;
    ~FreeMemoryRegion();

    static std::unique_ptr<FreeMemoryRegion> create(std::span<std::byte> region) noexcept;

    [[nodiscard]] std::size_t getSize() const noexcept
    {
        return size;
    }

    [[nodiscard]] FreeMemoryRegion* getNextFreeRegion() const noexcept
    {
        return nextFreeRegion;
    }

    [[nodiscard]] FreeMemoryRegion* getNext() const noexcept
    {
        return next;
    }

    [[nodiscard]] FreeMemoryRegion* addFreeRegion(std::span<std::byte> region) noexcept;

    struct MemoryClaimResult {
        FreeMemoryRegion* claimedRegion{ nullptr };
        FreeMemoryRegion* regionToReplaceClaimed{ nullptr };
    };

    [[nodiscard]] MemoryClaimResult claimMemory(std::size_t claimSize) noexcept;

    friend void swap(FreeMemoryRegion& first, FreeMemoryRegion& second) noexcept;

private:
    FreeMemoryRegion(std::size_t size, FreeMemoryRegion* nextFreeRegion, FreeMemoryRegion* next) noexcept
        : size{ size }, nextFreeRegion{ nextFreeRegion }, next{ next }
    {
    }

    std::size_t size;
    FreeMemoryRegion* nextFreeRegion;
    FreeMemoryRegion* next;
};

FreeMemoryRegion::FreeMemoryRegion(FreeMemoryRegion&& other) noexcept
    : size{ other.size }, nextFreeRegion{ other.nextFreeRegion }, next{ other.next }
{
    other.size = 0;
    other.nextFreeRegion = nullptr;
    other.next = nullptr;
}

FreeMemoryRegion& FreeMemoryRegion::operator=(FreeMemoryRegion&& other) noexcept
{
    if (this != &other) {
        size = other.size;
        nextFreeRegion = other.nextFreeRegion;
        next = other.next;

        other.size = 0;
        other.nextFreeRegion = nullptr;
        other.next = nullptr;
    }
    return *this;
}

FreeMemoryRegion::~FreeMemoryRegion()
{
    if (nextFreeRegion != nullptr) {
        delete nextFreeRegion;
    }
}

void swap(FreeMemoryRegion& first, FreeMemoryRegion& second) noexcept
{
    using std::swap;
    swap(first.size, second.size);
    swap(first.nextFreeRegion, second.nextFreeRegion);
    swap(first.next, second.next);
}

std::unique_ptr<FreeMemoryRegion> FreeMemoryRegion::create(std::span<std::byte> region) noexcept
{
    return std::unique_ptr<FreeMemoryRegion>{ new FreeMemoryRegion{ region.size(), nullptr, region.data() } };
}

FreeMemoryRegion* FreeMemoryRegion::addFreeRegion(std::span<std::byte> region) noexcept
{
    if (shouldPrepend(region.data())) {
        return prependRegion(region);
    }
    return findRegionToAppendTo(region.data()).appendRegion(region);
}

FreeMemoryRegion::MemoryClaimResult FreeMemoryRegion::claimMemory(std::size_t claimSize) noexcept
{
    if (claimMemoryFromSelf(claimSize)) {
        return MemoryClaimResult{ this, nextFreeRegion };
    }

    for (FreeMemoryRegion* region = this; region->nextFreeRegion != nullptr; region = region->nextFreeRegion) {
        if (region->nextFreeRegion->claimMemoryFromSelf(claimSize)) {
            const auto claimedRegion = region->nextFreeRegion;
            region->nextFreeRegion = claimedRegion->nextFreeRegion;
            return MemoryClaimResult{ claimedRegion, region->nextFreeRegion };
        }
    }

    return {};
}

FreeMemoryRegion* FreeMemoryRegion::prependRegion(std::span<std::byte> region) noexcept
{
    if (region.data() + region.size() == reinterpret_cast<std::byte*>(this)) {
        return new FreeMemoryRegion{ size + region.size(), nextFreeRegion, reinterpret_cast<FreeMemoryRegion*>(this) };
    } else {
        return new FreeMemoryRegion{ region.size(), this, reinterpret_cast<FreeMemoryRegion*>(this) };
    }
}

void FreeMemoryRegion::appendRegion(std::span<std::byte> region) noexcept
{
    if (reinterpret_cast<std::byte*>(this) + size == region.data()) {
        size += region.size();
        tryMergeWithNextRegion();
    } else {
        next = new FreeMemoryRegion{ region.size(), next, reinterpret_cast<FreeMemoryRegion*>(this) };
        next->tryMergeWithNextRegion();
    }
}

FreeMemoryRegion& FreeMemoryRegion::findRegionToAppendTo(std::byte* newRegionPointer) noexcept
{
    FreeMemoryRegion* region = this;
    while (region != nullptr && region->getNext() != nullptr && std::less<>{}(reinterpret_cast<std::byte*>(region->getNext()), newRegionPointer)) {
        region = region->getNext();
    }
    return *region;
}

bool FreeMemoryRegion::shouldPrepend(const std::byte* newRegionPointer) const noexcept
{
    return std::less<>{}(newRegionPointer, reinterpret_cast<const std::byte*>(this));
}

void FreeMemoryRegion::tryMergeWithNextRegion() noexcept
{
    if (reinterpret_cast<std::byte*>(this) + size == reinterpret_cast<std::byte*>(nextFreeRegion)) {
        size += nextFreeRegion->size;
        nextFreeRegion = nextFreeRegion->nextFreeRegion;
    }
}
