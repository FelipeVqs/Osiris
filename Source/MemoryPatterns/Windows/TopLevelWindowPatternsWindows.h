#pragma once

#include <cstdint>
#include <memory>

#include "MemoryPatterns/TopLevelWindowPatterns.h"
#include "MemorySearch/BytePatternLiteral.h"

namespace {
constexpr auto PANORAMA_PATTERN = BytePatternLiteral("F3 0F 11 49 ? 48 8B F9");
}

namespace MemoryPatterns {

inline UiScaleFactorOffset TopLevelWindowPatterns::uiScaleFactorOffset() const noexcept {
    auto pattern_finder = std::make_unique<PatternFinder>(PANORAMA_PATTERN);
    const auto pattern_address = pattern_finder->find();
    if (!pattern_address) {
        return 0;
    }
    return pattern_address.add(4).readOffset<UiScaleFactorOffset>();
}

}  // namespace MemoryPatterns
