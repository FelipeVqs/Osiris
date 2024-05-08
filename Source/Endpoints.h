#pragma once

#include "GlobalContext/GlobalContext.h"
#include "Hooks/PeepEventsHook.h"
#include "Utils/ReturnAddress.h"

extern "C"
{

// Returns the original `SDL_PeepEvents` function, or a null pointer if the hook has been unloaded
sdl3::SDL_PeepEvents* SDLHook_PeepEvents_cpp() noexcept
{
    auto& globalContext = GlobalContext::instance();
    if (!globalContext) {
        // Handle error
        return nullptr;
    }

    const auto [original, shouldUnload] = globalContext.peepEventsHook();
    if (shouldUnload) {
        globalContext.destroyInstance();
    }
    return original;
}

// Returns the `getWorldSession` function with the specified return address hooked, or the original function if the hook has been unloaded
cs2::CLoopModeGame::getWorldSession LoopModeGameHook_getWorldSession_cpp(const void* returnAddress) noexcept
{
    auto& globalContext = GlobalContext::instance();
    if (!globalContext) {
        // Handle error
        return {};

