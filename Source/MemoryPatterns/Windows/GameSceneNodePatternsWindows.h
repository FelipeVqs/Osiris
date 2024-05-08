#pragma once

#include <MemoryPatterns/GameSceneNodePatterns.h>
#include <MemorySearch/BytePatternLiteral.h>

inline OffsetToAbsOrigin GameSceneNodePatterns::getAbsoluteOriginOffset() const noexcept
{
    // Search for the pattern with a timeout of 1000 milliseconds
    const auto patternResult = clientPatternFinder.find("F3 0F 11 97 ? ? ? ? 0F 28 C2"_pat, 1000);
    if (!patternResult) {
        // Handle error here, e.g. by logging or throwing an exception
        std::cerr << "Error searching for pattern: " << patternResult.error() << std::endl;
        return OffsetToAbsOrigin{};
    }

    // Calculate the offset relative to the start of the pattern
    const auto offset = patternResult.add(4).readOffset<OffsetToAbsOrigin>();
    if (!offset) {
        // Handle error here, e.g. by logging or throwing an exception
        std::cerr << "Error reading offset: " << offset.error() << std::endl;
        return OffsetToAbsOrigin{};
    }

    return *offset;
}
