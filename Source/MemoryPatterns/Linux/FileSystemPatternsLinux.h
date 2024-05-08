#pragma once

#include <MemoryPatterns/FileSystemPatterns.h>
#include <MemorySearch/BytePatternLiteral.h>
#include <optional>

namespace cs2 = concrete_slab;

namespace
{
    constexpr auto kFileSystemPattern = BytePatternLiteral("48 8D 05 ? ? ? ? 48 89 DA 4C 8B 00"_pat);
    constexpr auto kFileNamesOffsetPattern = BytePatternLiteral("48 8D BB ? ? ? ? E8 ? ? ? ? 8B 83 ? ? ? ? 89 C2"_pat);
}

class FileSystemPatterns
{
public:
    std::optional<cs2::CBaseFileSystem**> fileSystem() const
    {
        return constoverload(FileSystemPatterns::fileSystem, this)(kFileSystemPattern).add(3).abs().as<cs2::CBaseFileSystem**>();
    }

    std::optional<FileNamesOffset> fileNamesOffset() const
    {
        auto patternResult = constoverload(FileSystemPatterns::fileNamesOffset, this)(kFileNamesOffsetPattern);
        if (!patternResult.has_value())
            return std::nullopt;

        auto offset = patternResult.value().add(3).readOffset<FileNamesOffset>();
        if (offset.has_value())
            return offset;

        return std::nullopt;
    }

private:
    template <typename T>
    static auto constoverload(T* obj, auto pattern)
    {
        if constexpr (std::is_const_v<std::remove_pointer_t<T>>)
            return obj->template fileSystemPatternFinder<std::remove_pointer_t<T>>(pattern);
        else
            return obj->fileSystemPatternFinder(pattern);
    }
};
