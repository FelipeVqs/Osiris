#pragma once

#include <cstddef>
#include <span>
#include <stdexcept>
#include <system_error>

#include "FileDescriptor.h"
#include <Platform/Linux/LinuxPlatformApi.h>

struct LinuxInputFile {
public:
    explicit LinuxInputFile(const char* path) noexcept(false)
        : fileDescriptor{LinuxPlatformApi::open(path, O_RDONLY)}
    {
        if (!fileDescriptor) {
            throw std::runtime_error("Failed to open file");
        }
    }

    [[nodiscard]] std::size_t read(std::size_t fileOffset, std::span<std::byte> buffer) const noexcept(false)
    {
        const auto readBytes{LinuxPlatformApi::pread(fileDescriptor.get(), buffer.data(), buffer.size(), fileOffset)};
        if (readBytes == -1) {
            throw std::system_error(errno, std::generic_category(), "Failed to read file");
        }
        return readBytes;
    }

    LinuxInputFile(const LinuxInputFile&) = delete;
    LinuxInputFile(LinuxInputFile&&) = delete;
    LinuxInputFile& operator=(const LinuxInputFile&) = delete;
    LinuxInputFile& operator=(LinuxInputFile&&) = delete;

private:
    FileDescriptor fileDescriptor;
};
