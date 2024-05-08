#pragma once

#include <Windows.h>
#include <memory>
#include <optional>
#include <string>

#include "PebLdr.h"
#include "PortableExecutable.h"
#include "WindowsPlatformApi.h"
#include "WindowsVmtFinderParams.h"

class WindowsDynamicLibrary {
public:
    explicit WindowsDynamicLibrary(const std::string& libraryName)
        : handle{ PebLdr{ WindowsPlatformApi::getPeb()->ldr }.getModuleHandle(libraryName.c_str()) } {
        assert(handle != nullptr);
    }

    explicit operator bool() const {
        return handle != nullptr;
    }

    std::optional<GenericPointer> getFunctionAddress(const std::string& functionName) const {
        if (handle) {
            const auto pe = PortableExecutable{ reinterpret_cast<const std::byte*>(handle) };
            return pe.getExport(functionName);
        }
        return std::nullopt;
    }

    std::optional<MemorySection> getCodeSection() const {
        if (handle) {
            const auto pe = PortableExecutable{ reinterpret_cast<const std::byte*>(handle) };
            return pe.getCodeSection();
        }
        return std::nullopt;
    }

    std::optional<MemorySection> getVmtSection() const {
        if (handle) {
            const auto pe = PortableExecutable{ reinterpret_cast<const std::byte*>(handle) };
            return pe.getVmtSection();
        }
        return std::nullopt;
    }

    std::optional<MemorySection> getDataSection() const {
        if (handle) {
            const auto pe = PortableExecutable{ reinterpret_cast<const std::byte*>(handle) };
            return pe.getDataSection();
        }
        return std::nullopt;
    }

    WindowsVmtFinderParams getVmtFinderParams() const {
        return {getDataSection(), getVmtSection(), handle};
    }

    HMODULE getHandle() const {
        return handle;
    }

private:
    std::optional<PortableExecutable> portableExecutable() const {
        assert(handle != nullptr);
        return PortableExecutable{ reinterpret_cast<const std::byte*>(handle) };
    }

    HMODULE handle;
};
