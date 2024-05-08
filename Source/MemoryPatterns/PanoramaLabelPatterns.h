#pragma once

#include <CS2/Classes/Panorama.h>
#include <Helpers/PatternNotFoundLogger.h>
#include <MemorySearch/PatternFinder.h>

struct PanoramaLabelPatterns {
    cs2::CLabel::Constructor* constructor() const noexcept;
    cs2::CLabel::setTextInternal* setTextInternal() const noexcept;
    std::uint32_t* size() const noexcept;

    const PatternFinder<PatternNotFoundLogger>& clientPatternFinder;

    PanoramaLabelPatterns(const PatternFinder<PatternNotFoundLogger>& patternFinder) noexcept
        : clientPatternFinder(patternFinder) {}

    [[nodiscard]] cs2::CLabel::Constructor* constructor() const noexcept {
        // implementation here
    }

    [[nodiscard]] cs2::CLabel::setTextInternal* setTextInternal() const noexcept {
        // implementation here
    }

    [[nodiscard]] std::uint32_t* size() const noexcept {
        // implementation here
    }
};
