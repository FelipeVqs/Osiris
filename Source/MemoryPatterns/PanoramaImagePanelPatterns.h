#pragma once

#include <cstdint>
#include <memory>

#include <CS2/Classes/Panorama.h>
#include <GameClasses/OffsetTypes/PanoramaImagePanelOffset.h>
#include <Helpers/PatternNotFoundLogger.h>
#include <MemorySearch/PatternFinder.h>

class PanoramaImagePanelPatterns {
public:
    PanoramaImagePanelPatterns(const PatternFinder<PatternNotFoundLogger>& clientPatternFinder) noexcept;

    [[nodiscard]] std::unique_ptr<cs2::CImagePanel::SetImage> setImage() const;
    [[nodiscard]] std::unique_ptr<cs2::CImagePanel::Constructor> constructor() const;
    [[nodiscard]] std::uint32_t* size() const noexcept;
    [[nodiscard]] ImagePropertiesOffset imagePropertiesOffset() const noexcept;
    [[nodiscard]] OffsetToImagePath offsetToImagePath() const noexcept;

private:
    const PatternFinder<PatternNotFoundLogger>& clientPatternFinder;
};

PanoramaImagePanelPatterns::PanoramaImagePanelPatterns(const PatternFinder<PatternNotFoundLogger>& clientPatternFinder) noexcept
    : clientPatternFinder(clientPatternFinder) {}

std::unique_ptr<cs2::CImagePanel::SetImage> PanoramaImagePanelPatterns::setImage() const {
    // Implementation goes here
}

std::unique_ptr<cs2::CImagePanel::Constructor> PanoramaImagePanelPatterns::constructor() const {
    // Implementation goes here
}
