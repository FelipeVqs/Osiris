#pragma once

#include <CS2/Constants/DllNames.h>
#include <SDL/SdlConstants.h>
#include <SDL/SdlDll.h>
#include <SDL/SdlFunctions.h>
#include "LinuxDynamicLibrary.h"

class LinuxMessageBox {
public:
    LinuxMessageBox() noexcept
        : showSimpleMessageBox_(SdlDll{}.showSimpleMessageBox()) {
        if (!showSimpleMessageBox_) {
            // Handle error
        }
    }

    ~LinuxMessageBox() noexcept {
        destroy();
    }

    void showWarning(const char* title, const char* message) const noexcept {
        showMessageBox(title, message, sdl3::SDL_MESSAGEBOX_WARNING);
    }

    void showError(const char* title, const char* message) const noexcept {
        showMessageBox(title, message, sdl3::SDL_MESSAGEBOX_ERROR);
    }

private:
    void showMessageBox(const char* title, const char* message, unsigned int flags) const noexcept {
        if (showSimpleMessageBox_) {
            showSimpleMessageBox_(flags, title, message, nullptr);
        }
    }

    void destroy() noexcept {
        if (showSimpleMessageBox_) {
            SdlDll{}.destroyShowSimpleMessageBox(showSimpleMessageBox_);
            showSimpleMessageBox_ = nullptr;
        }
    }

    sdl3::SDL_ShowSimpleMessageBox* showSimpleMessageBox_;
};
