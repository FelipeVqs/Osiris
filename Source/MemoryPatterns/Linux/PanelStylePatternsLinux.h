#pragma once

#include <MemoryPatterns/PanelStylePatterns.h>
#include <MemorySearch/BytePatternLiteral.h>
#include <optional>

// Returns a pointer to the SetProperty function in the PanelStyle module.
// Returns nullopt if the pattern is not found.
std::optional<cs2::CPanelStyle::SetProperty*> PanelStylePatterns::setProperty() const noexcept {
    auto pattern = panoramaPatternFinder("E9 ? ? ? ? 0F 1F 00 48 8B 78 08"_pat).add(1).abs();
    if (!pattern.matched()) {
        return std::nullopt;
    }
    return pattern.as<cs2::CPanelStyle::SetProperty*>();
}

// Returns a pointer to the StylePropertySymbols struct in the PanelStyle module.
// Returns nullopt if the pattern is not found.
std::optional<cs2::CPanelStyle::StylePropertySymbols*> PanelStylePatterns::stylePropertiesSymbols() const noexcept {
    auto pattern1 = panoramaPatternFinder("48 89 75 ? E8 ? ? ? ? ? 89 ? 4C 89 ? 48 C7"_pat).add(5).abs();
    if (!pattern1.matched()) {
        return std::nullopt;
    }
    auto pattern2 = pattern1.matchPatternAtAddress(pattern1.address(), "0F B6 05 ? ? ? ? 84 C0 74 0D 48 8D 05 ? ? ? ?"_pat).add(14).abs();
    if (!pattern2.matched()) {
        return std::nullopt;
    }
    return pattern2.as<cs2::CPanelStyle::StylePropertySymbols*>();
}
