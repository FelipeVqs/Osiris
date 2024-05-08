#pragma once

#include <MemoryPatterns/SdlPatterns.h>
#include <MemorySearch/BytePatternLiteral.h>

/// Returns the address of the \c sdl3::SDL_PeepEvents pointer using the given \c peepEvents pointer.
/// \param peepEvents The starting point for the pattern search.
/// \return The address of the \c sdl3::SDL_PeepEvents pointer if a match is found, or \c nullptr otherwise.
sdl3::SDL_PeepEvents** SdlPatterns::peepEventsPointer(sdl3::SDL_PeepEvents* peepEvents) const noexcept
{
    // Use a static pattern for better readability
    constexpr BytePatternLiteral kPattern = {"48 FF 25 ? ? ? ?"_pat};

    // Calculate the absolute address of the pattern match
    const auto matchAddress = sdlPatternFinder.matchPatternAtAddress((void*)peepEvents, kPattern).add(3).abs();

    // Check if the match is valid before casting
    if (matchAddress.isValid()) {
        return matchAddress.as<sdl3::SDL_PeepEvents**>();
    }

    // Return nullptr if the match is not found
    return nullptr;
}
