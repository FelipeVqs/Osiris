#pragma once

#include <MemoryPatterns/PanelPatterns.h>
#include <MemorySearch/BytePatternLiteral.h>
#include <type_traits>

template <typename T>
using EnableIfNonConst = std::enable_if_t<!std::is_const_v<T>, T>;

inline EnableIfNonConst<cs2::CPanel2D::Create*> PanelPatterns::create() noexcept
{
    constexpr auto pattern = BytePatternLiteral("55 48 89 E5 41 56 49 89 FE 41 55 41 54 49 89 F4 48 83 EC 08 48 85 F6 74 0C 48 8B 06 48 89 F7 FF 50 50 49 89 C4 BF ? ? ? ? E8 ? ? ? ? 4C 89 F1"_pat);
    return static_cast<EnableIfNonConst<cs2::CPanel2D::Create*>>(clientPatternFinder(pattern).as<cs2::CPanel2D::Create*>());
}
