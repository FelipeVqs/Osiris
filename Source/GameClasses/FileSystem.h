#pragma once

#include <CS2/Classes/FileSystem.h>
#include "FileNameSymbolTable.h"
#include "Implementation/FileSystemImpl.h"

// Use this alias to avoid having to write cs2::CBaseFileSystem repeatedly.
using CS2FileSystem = cs2::CBaseFileSystem;

struct FileSystem {
    // Initialize member variables in the constructor initializer list.
    explicit FileSystem(CS2FileSystem& thisptr, const FileSystemImpl& impl) noexcept
        : thisptr{thisptr}
        , impl{impl}
    {}

    // Add a const qualifier to indicate that this method does not modify the object.
    [[nodiscard]] FileNameSymbolTable fileNames() const noexcept {
        // Explain the purpose of this method.
        /**
         * @return A FileNameSymbolTable object that maps file names to file offsets.
         */
        return FileNameSymbolTable{impl.fileNamesOffset.of(&thisptr).get()};
    }

private:
    CS2FileSystem& thisptr;
    const FileSystemImpl& impl;
};
