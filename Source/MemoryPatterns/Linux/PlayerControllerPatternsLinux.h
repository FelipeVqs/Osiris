#pragma once

#include <array>
#include <optional>
#include <span>
#include <memory>
#include <mutex>
#include <type_traits>

#include <MemoryPatterns/PlayerControllerPatterns.h>
#include <MemorySearch/BytePatternLiteral.h>

class PlayerControllerPatterns {
public:
    constexpr std::optional<std::int32_t> offsetToPlayerPawnHandle() const noexcept {
        return findOffset("F8 48 85 C0 74 ? 8B 88 ? ? ? ?", 8, 8);
    }

    constexpr std::optional<std::int32_t> offsetToPlayerColor() const noexcept {
        return findOffset("49 63 9C 24 ? ? ? ? 83 FB 04", 4, 4);
    }

private:
    template<std::size_t N, std::size_t M>
    std::optional<std::int32_t> findOffset(const std::array<std::byte, N>& pattern, std::size_t skipBytes, std::size_t addValue) const noexcept {
        std::scoped_lock lock(mutex_);
        auto result = patternFinder_.find(pattern);
        if (result.empty()) {
            return std::nullopt;
        }
        auto offset = result.add(skipBytes).read<std::int32_t>();
        return offset + addValue;
    }

    mutable std::mutex mutex_;
    BytePatternFinder patternFinder_;
};

