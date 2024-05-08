#pragma once

#include <cstddef>
#include <span>
#include <Windows.h>
#include <winternl.h>

#include <Platform/Windows/NtHandle.h>
#include "WindowsFileSystem.h"

using Byte = std::byte;

struct WindowsInputFile {
    explicit WindowsInputFile(UNICODE_STRING fileName) noexcept
        : handle{WindowsFileSystem::openFileForReading(fileName)}
    {
        if (!handle) {
            // Handle error
        }
    }

    [[nodiscard]] std::size_t read(std::size_t fileOffset, std::span<Byte> buffer) const noexcept
    {
        if (!handle) {
            // Handle error
            return 0;
        }

        return WindowsFileSystem::readFile(handle.get(), fileOffset, buffer);
    }

private:
    NtHandle handle;
};
