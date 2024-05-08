#pragma once

#include <cassert>
#include <memory>

#include <SDL/SdlFunctions.h>

extern "C" int SDLHook_PeepEvents_asm(void* events, int numevents, int action, unsigned minType, unsigned maxType) noexcept;

class PeepEventsHook {
public:
    /// Constructs a PeepEventsHook object with the given peepEvents pointer.
    explicit PeepEventsHook(sdl3::SDL_PeepEvents* peepEvents) noexcept
        : peepEventsPointer{peepEvents}
    {
    }

    /// Returns true if the PeepEventsHook object is valid (i.e., the peepEventsPointer is not null).
    [[nodiscard]] bool isValid() const noexcept
    {
        return peepEventsPointer != nullptr;
    }

    /// Enables the hook by replacing the original peepEvents function with the hook function.
    void enable() noexcept
    {
        if (!isValid()) {
            throw std::runtime_error("PeepEventsHook is not valid");
        }
        original = std::exchange(peepEventsPointer, &SDLHook_PeepEvents_asm);
    }

    /// Disables the hook by restoring the original peepEvents function.
    void disable() const noexcept
    {
        if (!isValid()) {
            throw std::runtime_error("PeepEventsHook is not valid");
        }
        peepEventsPointer = original.get();
    }

    /// Releases any resources held by the PeepEventsHook object.
    ~PeepEventsHook() noexcept
    {
        dispose();
    }

    /// Releases any resources held by the PeepEventsHook object.
    void dispose() noexcept
    {
        if (isValid()) {
            disable();
        }
    }

private:
    sdl3::SDL_PeepEvents* peepEventsPointer;
    std::unique_ptr<sdl3::SDL_PeepEvents> original;
};
