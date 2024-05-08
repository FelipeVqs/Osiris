#pragma once

#include <MemoryPatterns/EntitySystemPatterns.h>
#include <MemorySearch/BytePatternLiteral.h>
#include <optional>
#include <system_error>

namespace
{
    constexpr auto& entitySystemPattern = "48 8B 0D ? ? ? ? 48 8D 94 24 ? ? ? ? 33 DB"_pat;
    constexpr auto& highestEntityIndexOffsetPattern = "3B 8F ? ? ? ? 7E 06"_pat;
    constexpr auto& entityListOffsetPattern = "48 8D 4B ? E8 ? ? ? ? 8D 85"_pat;
}

inline std::optional<cs2::CGameEntitySystem**> EntitySystemPatterns_entitySystem(EntitySystemPatterns& self) noexcept
{
    try
    {
        return self.clientPatternFinder(entitySystemPattern).add(3).abs().as<cs2::CGameEntitySystem**>();
    }
    catch (const std::exception&)
    {
        return std::nullopt;
    }
}

inline std::optional<cs2::HighestEntityIndexOffset> EntitySystemPatterns_highestEntityIndexOffset(EntitySystemPatterns& self) noexcept
{
    try
    {
        return self.clientPatternFinder(highestEntityIndexOffsetPattern).add(2).readOffset<cs2::HighestEntityIndexOffset>();
    }
    catch (const std::exception&)
    {
        return std::nullopt;
    }
}

inline std::optional<cs2::EntityListOffset> EntitySystemPatterns_entityListOffset(EntitySystemPatterns& self) noexcept
{
    try
    {
        return self.clientPatternFinder(entityListOffsetPattern).add(3).readOffset<cs2::EntityListOffset>();
    }
    catch (const std::exception&)
    {
        return std::nullopt;
    }
}
