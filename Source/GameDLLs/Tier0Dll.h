#pragma once

#include <CS2/Classes/CUtlFilenameSymbolTable.h>
#include <CS2/Constants/DllNames.h>
#include <Platform/DynamicLibrary.h>
#include <Platform/Macros/IsPlatform.h>

namespace cs2
{
    struct IMemAlloc;
}

class Tier0Dll : public DynamicLibrary {
public:
    Tier0Dll() noexcept
        : DynamicLibrary{ cs2::TIER0_DLL }
    {
    }

    [[nodiscard]] const cs2::CUtlFilenameSymbolTable::String* filenameSymbolTableString() const noexcept
    {
        return getFunctionAddress<cs2::CUtlFilenameSymbolTable::String>("?String@CUtlFilenameSymbolTable@@QEAA_NAEBIPEADH@Z")
#if IS_WIN64()
            .value();
#elif IS_LINUX()
        .value_or(nullptr);
#endif
    }

    [[nodiscard]] const cs2::IMemAlloc** memAlloc() const noexcept
    {
        return getFunctionAddress<cs2::IMemAlloc**>("g_pMemAlloc").value();
    }

private:
    template<typename T>
    std::unique_ptr<T> getFunctionAddress(const char* name) const noexcept
    {
        auto addr = getFunctionAddress(name);
        if (addr)
            return std::unique_ptr<T>(reinterpret_cast<T>(addr));
        return std::unique_ptr<T>();
    }
};
