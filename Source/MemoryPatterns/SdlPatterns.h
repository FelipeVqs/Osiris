#pragma once

#include <Helpers/PatternNotFoundLogger.h>
#include <MemorySearch/PatternFinder.h>
#include <SDL/SdlFunctions.h>

// Use `std::unique_ptr` to manage the memory of `sdl3::SDL_PeepEvents**`
class SdlPatterns {
public:
    explicit SdlPatterns(sdl3::SDL_PeepEvents* peepEvents) noexcept
        : peepEventsPointer_(std::make_unique<sdl3::SDL_PeepEvents*>(peepEvents)) {}

    [[nodiscard]] sdl3::SDL_PeepEvents** peepEventsPointer() const noexcept {
        return peepEventsPointer_.get();
    }

    const PatternFinder<PatternNotFoundLogger>& getSdlPatternFinder() const noexcept {
        return sdlPatternFinder_;
    }

private:
    std::unique_ptr<sdl3::SDL_PeepEvents*> peepEventsPointer_;
    PatternFinder<PatternNotFoundLogger> sdlPatternFinder_;
};
