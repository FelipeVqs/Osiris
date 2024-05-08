#pragma once

#include <ShlObj_core.h>
#include <optional>
#include <Platform/Windows/WindowsDynamicLibrary.h>

struct Shell32Dll : WindowsDynamicLibrary {
public:
    Shell32Dll() : WindowsDynamicLibrary{ "shell32.dll" }
    {
        if (!isLoaded()) {
            throw std::runtime_error("Failed to load shell32.dll");
        }
    }

    explicit Shell32Dll(bool load) : Shell32Dll() {
        if (load) {
            load();
        }
    }

    [[nodiscard]] std::optional<decltype(&::SHGetKnownFolderPath)> SHGetKnownFolderPath() const noexcept {
        if (auto addr = getFunctionAddress("SHGetKnownFolderPath")) {
            return addr.as<decltype(&::SHGetKnownFolderPath)>();
        }
        return std::nullopt;
    }

    void load() const {
        loadLibrary();
    }
};
