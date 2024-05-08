#pragma once

#include <MemoryPatterns/MemAllocPatterns.h>
#include <MemorySearch/BytePatternLiteral.h>
#include <stdexcept>

namespace
{
    constexpr BytePatternLiteral clientPattern{"FF 50 ? 48 89 43 ? 4C 8D"_pat};
}

inline std::int8_t* MemAllocPatterns::allocOffset() const
{
    const auto patternResult = clientPattern.find(getClientMemory());
    if (!patternResult)
    {
        throw std::runtime_error("Client pattern not found");
    }

    const auto offsetResult = patternResult.add(2);
    if (!offsetResult)
    {
        throw std::runtime_error("Failed to calculate offset");
    }

    return offsetResult.as<std::int8_t*>();
}
