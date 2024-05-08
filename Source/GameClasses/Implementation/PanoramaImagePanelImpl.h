#pragma once

#include <CS2/Classes/Panorama.h>
#include <MemoryPatterns/PanoramaImagePanelPatterns.h>

struct PanoramaImagePanelImpl {
    // Constructor
    PanoramaImagePanelImpl(const PanoramaImagePanelPatterns& panoramaImagePanelPatterns) noexcept
        : setImage(panoramaImagePanelPatterns.setImage())
        , constructor(panoramaImagePanelPatterns.constructor())
        , size(panoramaImagePanelPatterns.size())
        , imagePropertiesOffset(panoramaImagePanelPatterns.imagePropertiesOffset())
        , offsetToImagePath(panoramaImagePanelPatterns.offsetToImagePath()) {}

    // Returns a const reference to the singleton instance of PanoramaImagePanelImpl
    static const PanoramaImagePanelImpl& instance() noexcept {
        static PanoramaImagePanelImpl instance{PanoramaImagePanelPatterns::get()};
        return instance;
    }

    // Pointer to the setImage function of cs2::CImagePanel
    cs2::CImagePanel::SetImage* setImage;

    // Pointer to the constructor function of cs2::CImagePanel
    cs2::CImagePanel::Constructor* constructor;

    // Pointer to the size variable of cs2::CImagePanel
    std::uint32_t* size;

    // The offset of the imageProperties variable of cs2::CImagePanel
    ImagePropertiesOffset imagePropertiesOffset;

    // The offset of the imagePath variable of cs2::CImagePanel
    OffsetToImagePath offsetToImagePath;
};
