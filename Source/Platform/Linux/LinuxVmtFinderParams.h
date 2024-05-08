#pragma once

#include <Windows.h>
#include <WinNT.h>

// Define the maximum size of a memory section, in bytes
#define MAX_MEMORY_SECTION_SIZE 0x10000

// Define the struct for the LinuxVmtFinderParams
typedef struct _LinuxVmtFinderParams {
    // The base address of the read-only data section
    PVOID rodataSectionBase;

    // The size of the read-only data section
    SIZE_T rodataSectionSize;

    // The base address of the read-write data section
    PVOID dataRelRoSectionBase;

    // The size of the read-write data section
    SIZE_T dataRelRoSectionSize;
} LinuxVmtFinderParams;

// Function to initialize the LinuxVmtFinderParams struct
// Returns TRUE on success, FALSE on failure
BOOL InitializeLinuxVmtFinderParams(LinuxVmtFinderParams* params)
{
    // Check if the parameters are valid
    if (params == NULL) {
        SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;
    }

    // Get the base address and size of the .rodata section
    MEMORY_BASIC_INFORMATION rodataInfo;
    if (!VirtualQuery((LPCVOID)0x08048000, &rodataInfo, sizeof(rodataInfo))) {
        return FALSE;
    }

    // Check if the .rodata section is within the valid address range
    if (rodataInfo.BaseAddress < (PVOID)0x08048000 ||
        rodataInfo.BaseAddress >= (PVOID)0x08049000) {
        SetLastError(ERROR_INVALID_DATA);
        return FALSE;
    }

    // Set the read-only data section parameters
    params->rodataSectionBase = rodataInfo.BaseAddress;
    params->rodataSectionSize = rodataInfo.RegionSize;

    // Get the base address and size of the .data.rel.ro section
    MEMORY_BASIC_INFORMATION dataRelRoInfo;
    if (!VirtualQuery((LPCVOID)0x0804A000, &dataRelRoInfo, sizeof(dataRelRoInfo))) {
        return FALSE;
    }

    // Check if the .data.rel.ro section is within the valid address range
    if (dataRelRoInfo.BaseAddress < (PVOID)0x0804A000 ||
        dataRelRoInfo.BaseAddress >= (PVOID)0x0804B000) {
        SetLastError(ERROR_INVALID_DATA);
        return FALSE;
    }

    // Set the read-write data section parameters
    params->dataRelRoSectionBase = dataRelRoInfo.BaseAddress;
    params->dataRelRoSectionSize = dataRelRoInfo.RegionSize;

    // Check if the total size of the memory sections is within the maximum size
    if (params->rodataSectionSize + params->dataRelRoSectionSize > MAX_MEMORY_SECTION_SIZE) {
        SetLastError(ERROR_INVALID_DATA);
        return FALSE;
    }

    // Return success
    return TRUE;
}
