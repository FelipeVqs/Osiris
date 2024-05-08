#pragma once

#include <MemoryPatterns/SdlPatterns.h>
#include <MemorySearch/BytePatternLiteral.h>

/// Returns the address of the \c sdl3::SDL_PeepEvents pointer in memory that matches the given pattern.
/// \param peepEvents A pointer to the \c sdl3::SDL_PeepEvents function.
/// \return The address of the \c sdl3::SDL_PeepEvents pointer in memory that matches the given pattern.
[[nodiscard]] constexpr auto SdlPatterns::peepEventsPointer(sdl3::SDL_PeepEvents* peepEvents) const noexcept
{
    constexpr auto pattern = BytePatternLiteral::fromString("FF 25 ? ? ? ?"_pat);
    const auto matchResult = sdlPatternFinder.matchPatternAtAddress((void*)peepEvents, pattern);

    if (!matchResult) {
        return nullptr;
    }

    const auto matchAddress = matchResult.getMatchedAddress();
    const auto offset = matchResult.getPatternOffset();

    return reinterpret_cast<sdl3::SDL_PeepEvents**>(matchAddress + offset + 2);
}
