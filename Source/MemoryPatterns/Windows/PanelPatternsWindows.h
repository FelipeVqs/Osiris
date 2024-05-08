#pragma once

#include <MemoryPatterns/PanelPatterns.h>
#include <MemorySearch/BytePatternLiteral.h>
#include <memory>

namespace
{
    constexpr auto PANEL_CREATE_PATTERN = "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 30 48 8B F1 48 8B FA B9 ? ? ? ? E8 ? ? ? ? 48 8B D8 48 85 C0 74 5C"_pat;
}

inline std::unique_ptr<cs2::CPanel2D::Create> PanelPatterns::createPanel() const
{
    try
    {
        auto pattern_result = clientPatternFinder(PANEL_CREATE_PATTERN);
        return pattern_result.as<cs2::CPanel2D::Create*>();
    }
    catch (const std::exception& e)
    {
        // Log or handle the error here
        std::cerr << "Error finding panel create pattern: " << e.what() << std::endl;
        throw;
    }
}
