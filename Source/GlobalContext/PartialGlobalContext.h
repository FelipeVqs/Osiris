#pragma once

#include <CS2/Constants/DllNames.h>
#include <Hooks/PeepEventsHook.h>
#include <MemoryPatterns/SdlPatterns.h>
#include <Platform/DynamicLibrary.h>
#include <Platform/Macros/PlatformSpecific.h>
#include <SDL/SdlDll.h>

struct PartialGlobalContext final {
    // Default constructor
    PartialGlobalContext() = default;

    // Construct with SdlDll and SdlPatterns
    constexpr PartialGlobalContext(const SdlDll& sdlDll, const SdlPatterns& sdlPatterns) noexcept
        : peepEventsHook{sdlPatterns.peepEventsPointer(sdlDll.peepEvents())}
    {
    }

    // PeepEventsHook member
    PeepEventsHook peepEventsHook;

    // Enable the hook if it is valid
    void enableIfValid() noexcept
    {
        if (peepEventsHook.isValid() && peepEventsHook.getPeepEvents() != nullptr)
            peepEventsHook.enable();
    }
};
