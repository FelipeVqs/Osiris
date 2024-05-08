#pragma once

#include <cstddef>
#include <cstdio>
#include <span>
#include <Windows.h>
#include <winternl.h>

#include <Platform/Windows/Syscalls/WindowsSyscalls.h>

struct WindowsFileSystem {
    static HANDLE openFileForReading(UNICODE_STRING fileName) noexcept
    {
        HANDLE handle;
        IO_STATUS_BLOCK statusBlock{};
        OBJECT_ATTRIBUTES objectAttributes{
            .Length{sizeof(OBJECT_ATTRIBUTES)},
            .RootDirectory{nullptr},
            .ObjectName{&fileName},
            .Attributes{OBJ_CASE_INSENSITIVE},
            .SecurityDescriptor{nullptr},
            .SecurityQualityOfService{nullptr}
        };

        // Check if the file name is not empty
        if (fileName.Length == 0) {
            SetLastError(ERROR_INVALID_NAME);
            return nullptr;
        }

        if (NT_SUCCESS(WindowsSyscalls::NtCreateFile(&handle, FILE_GENERIC_READ, &objectAttributes, &statusBlock, nullptr, FILE_ATTRIBUTE_NORMAL, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, FILE_OPEN, FILE_SYNCHRONOUS_IO_NONALERT, nullptr, 0)))
            return handle;

        // Set the last error code based on the status block
        SetLastError(RtlNtStatusToDosError(statusBlock.Status));
        return nullptr;
    }

    static std::size_t readFile(HANDLE fileHandle, std::size_t fileOffset, std::span<std::byte> buffer) noexcept
    {
        IO_STATUS_BLOCK statusBlock{};
        LARGE_INTEGER offset{.QuadPart{static_cast<LONGLONG>(fileOffset)}};

        // Check if the file handle is not invalid
        if (fileHandle == INVALID_HANDLE_VALUE) {
            SetLastError(ERROR_INVALID_HANDLE);
            return 0;
        }

        // Check if the buffer size is not zero
        if (buffer.size() == 0) {
            SetLastError(ERROR_INVALID_PARAMETER);
            return 0;
        }

        if (NT_SUCCESS(WindowsSyscalls::NtReadFile(fileHandle, nullptr, nullptr, nullptr, &statusBlock, buffer.data(), static_cast<ULONG>(buffer.size()), &offset, nullptr)) && statusBlock.Information <= buffer.size()) {
            return statusBlock.Information;
        }

        // Set the last error code based on the status block
        SetLastError(RtlNtStatusToDosError(statusBlock.Status));
        return 0;
    }
};
