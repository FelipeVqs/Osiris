#pragma once

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <span>

#include <Utils/GenericPointer.h>

class PatternSearchResult {
public:
    PatternSearchResult(GenericPointer base, std::size_t patternFoundOffset, std::span<const std::byte> foundPatternBytes) noexcept
        : base_{base}
        , patternFoundOffset_{patternFoundOffset}
        , foundPatternBytes_{foundPatternBytes}
    {
        assert(base_);
    }

    PatternSearchResult() = default;

    PatternSearchResult& add(std::size_t offset) noexcept
    {
        if (base_) {
            extraOffset_ += offset;
            assert(extraOffset_ < foundPatternBytes_.size());
        }
        return *this;
    }

    [[nodiscard]] GenericPointer abs() const noexcept
    {
        if (base_) {
            using OffsetType = std::int32_t;
            OffsetType offset;
            assert(foundPatternBytes_.size() - extraOffset_ >= sizeof(OffsetType));
            std::memcpy(&offset, foundPatternBytes_.data() + extraOffset_, sizeof(OffsetType));
            return base_.as<const std::byte*>() + patternFoundOffset_ + extraOffset_ + sizeof(OffsetType) + offset;
        }
        return {};
    }

    template <typename FieldOffsetType>
    [[nodiscard]] FieldOffsetType readOffset() const noexcept
    {
        if (base_) {
            typename FieldOffsetType::OffsetType result;
            assert(foundPatternBytes_.size() - extraOffset_ >= sizeof(result));
            std::memcpy(&result, foundPatternBytes_.data() + extraOffset_, sizeof(result));
            return FieldOffsetType{result};
        }
        return {};
    }

    template <typename T>
    [[nodiscard]] T as() const noexcept
    {
        if (base_)
            return T(base_.as<const std::byte*>() + patternFoundOffset_ + extraOffset_);
        return T(base_.as<void*>());
    }

    // Disable implicit copying
    PatternSearchResult(const PatternSearchResult&) = default;
    PatternSearchResult& operator=(const PatternSearchResult&) = delete;

    // Disable implicit moving
    PatternSearchResult(PatternSearchResult&&) = delete;
    PatternSearchResult& operator=(PatternSearchResult&&) = delete;

private:
    GenericPointer base_;
    std::size_t patternFoundOffset_;
    std::span<const std::byte> foundPatternBytes_;
    std::size_t extraOffset_{0};
};
