#pragma once

#include <CS2/Classes/Panorama.h>
#include "Implementation/PanoramaLabelImpl.h"

// A wrapper class for the cs2::CLabel class
struct PanoramaLabel {
    // Constructor
    explicit PanoramaLabel(cs2::CLabel* thisptr) noexcept
        : thisptr{ thisptr }
    {
        // Ensure that the thisptr member is not null
        static_assert(thisptr != nullptr, "The thisptr member cannot be null.");
    }

    // A wrapper method for the setTextInternal method of the PanoramaLabelImpl class
    void setTextInternal(const char* value, int textType, bool trustedSource) const noexcept
    {
        // Check if the PanoramaLabelImpl instance exists and its setTextInternal method is callable
        if (PanoramaLabelImpl::instance().setTextInternal)
            PanoramaLabelImpl::instance().setTextInternal(thisptr, value, textType, trustedSource);
    }

private:
    // A pointer to the cs2::CLabel object
    cs2::CLabel* thisptr;
};
