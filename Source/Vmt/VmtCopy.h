#pragma once

#include <algorithm>
#include <cstdint>
#include <cstddef>
#include <memory>

#include <MemoryAllocation/UniquePtr.h>
#include <Platform/TypeInfoPrecedingVmt.h>
#include "VmtLength.h"

class VmtCopy {
public:
    /// Constructs a VmtCopy object with the given VMT and length.
    /// Copies the original VMT into a new VMT with type info preceding it.
    VmtCopy(std::unique_ptr<std::uintptr_t[]> vmt, VmtLength length) noexcept
        : originalVmt{ std::move(vmt) }
        , replacementVmtWithTypeInfo{ mem::makeUniqueForOverwrite<std::uintptr_t[]>(static_cast<std::size_t>(length) + platform::lengthOfTypeInfoPrecedingVmt) }
    {
        copyOriginalVmt();
    }

    /// Returns the replacement VMT with type info preceding it.
    [[nodiscard]] std::uintptr_t* getReplacementVmt() const noexcept
    {
        if (replacementVmtWithTypeInfo) [[likely]]
            return replacementVmtWithTypeInfo.get() + platform::lengthOfTypeInfoPrecedingVmt;
        return nullptr;
    }

    /// Returns the original VMT.
    [[nodiscard]] std::uintptr_t* getOriginalVmt() const noexcept
    {
        return originalVmt.get();
    }

    /// Destructor to release the memory allocated by replacementVmtWithTypeInfo.
    ~VmtCopy() = default;

private:
    /// Copies the original VMT into the replacement VMT with type info preceding it.
    void copyOriginalVmt() const noexcept
    {
        if (replacementVmtWithTypeInfo) [[likely]]
            std::copy_n(originalVmt.get() - platform::lengthOfTypeInfoPrecedingVmt, lengthWithTypeInfo(), replacementVmtWithTypeInfo.get());
    }

    /// Returns the length of the replacement VMT with type info preceding it.
    [[nodiscard]] std::size_t lengthWithTypeInfo() const noexcept
    {
        return replacementVmtWithTypeInfo.get_deleter().getNumberOfElements();
    }

    std::unique_ptr<std::uintptr_t[]> originalVmt;
    std::unique_ptr<std::uintptr_t[]> replacementVmtWithTypeInfo;
};
