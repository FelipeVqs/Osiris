#pragma once

#include <cstddef>
#include <span>

#include "VmtLength.h"
#include <Utils/MemorySection.h>

struct VmtLengthCalculator final {
    explicit VmtLengthCalculator(const MemorySection& codeSection, const MemorySection& vmtSection)
        : codeSection{ codeSection }, vmtSection{ vmtSection }
    {}

    [[nodiscard]] VmtLength operator()(const std::uintptr_t* vmt) const {
        std::size_t length = 0;
        while (isVmtEntry(vmt + length)) {
            ++length;
        }
        return VmtLength{ length };
    }

private:
    [[nodiscard]] constexpr static bool isVmtEntry(const std::uintptr_t* pointer) const {
        return vmtSection.contains(std::uintptr_t(pointer), sizeof(std::uintptr_t)) &&
               codeSection.contains(*pointer);
    }

    const MemorySection& codeSection;
    const MemorySection& vmtSection;
};
