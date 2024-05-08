#pragma once

#include <CS2/Classes/CUtlFilenameSymbolTable.h>
#include <GameDLLs/Tier0Dll.h>

struct FileNameSymbolTableImpl {
    explicit FileNameSymbolTableImpl(Tier0Dll tier0Dll) noexcept
        : string{ tier0Dll.filenameSymbolTableString() }
    {
    }

    ~FileNameSymbolTableImpl() = default;

    FileNameSymbolTableImpl(const FileNameSymbolTableImpl&) = delete;
    FileNameSymbolTableImpl& operator=(const FileNameSymbolTableImpl&) = delete;

    cs2::CUtlFilenameSymbolTable::String* string;

    static FileNameSymbolTableImpl instance;

    static const FileNameSymbolTableImpl& getInstance() noexcept {
        static constexpr bool initialized = []() {
            instance = FileNameSymbolTableImpl{ Tier0Dll() };
            return true;
        }();
        return instance;
    }
};

FileNameSymbolTableImpl FileNameSymbolTableImpl::instance;
