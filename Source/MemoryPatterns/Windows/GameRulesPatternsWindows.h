#pragma once

#include <MemoryPatterns/GameRulesPatterns.h>
#include <MemorySearch/BytePatternLiteral.h>

inline RoundStartTimeOffset GameRulesPatterns::getRoundStartTimeOffset() const noexcept
{
    // Find the pattern in memory
    auto patternResult = clientPatternFinder("F3 0F 5C C8 F3 0F 10 43 ? F3"_pat);
    if (!patternResult) {
        // Pattern not found, handle error
        return 0;
    }

    // Calculate the offset
    auto offset = patternResult.add(8).readOffset<RoundStartTimeOffset>();
    if (!offset) {
        // Failed to read offset, handle error
        return 0;
    }

    return *offset;
}
