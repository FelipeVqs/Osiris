#pragma once

#include <Utils/MemorySection.h>

// Forward declaration of the WindowsVmtFinder class
class WindowsVmtFinder;

// Struct containing parameters for the WindowsVmtFinder class
struct WindowsVmtFinderParams {
    // The data section of the memory
    MemorySection dataSection;

    // The read-only data section of the memory
    MemorySection rdataSection;

    // The base address of the DLL
    const void* dllBase;

    // Constructor for WindowsVmtFinderParams
    WindowsVmtFinderParams(MemorySection data_section, MemorySection rdata_section, const void* dll_base)
        : dataSection(data_section), rdataSection(rdata_section), dllBase(dll_base) {}
};

// Class for finding the VMT (Virtual Method Table) in Windows
class WindowsVmtFinder {
public:
    // Method for finding the VMT using the given parameters
    void* findVmt(const WindowsVmtFinderParams& params);
};
