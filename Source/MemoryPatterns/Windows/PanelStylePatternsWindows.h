#pragma once

#include <cstddef>
#include <stdexcept>

#include <MemoryPatterns/PanelStylePatterns.h>
#include <MemorySearch/BytePatternLiteral.h>

inline cs2::CPanelStyle::SetProperty* PanelStylePatterns::getProperty() const {
    if (const auto patternResult = panoramaPatternFinder("E8 ? ? ? ? 8B 45 B8"_pat)) {
        const auto offset = patternResult.add(1).abs();
        return offset.as<cs2::CPanelStyle::SetProperty*>();
    }
    throw std::runtime_error("Property pattern not found");
}

inline const cs2::CPanelStyle::StylePropertySymbols* PanelStylePatterns::stylePropertiesSymbols() const {
    if (const auto pointerToStylePropertySymbolsMemory = panoramaPatternFinder("48 8B 05 ? ? ? ? 48 63 FB"_pat)) {
        const auto offset = patternResult.add(3).abs();
        const auto memoryAddress = offset.as<std::byte*>();
        const auto stylePropertySymbolsAddress = reinterpret_cast<cs2::CPanelStyle::StylePropertySymbols*>(memoryAddress - offsetof(cs2::CPanelStyle::StylePropertySymbols, memory));
        return stylePropertySymbolsAddress;
    }
    return nullptr;
}
