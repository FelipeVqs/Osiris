#pragma once

#include <cstring>
#include <CS2/Classes/Panorama.h>
#include <Platform/Macros/FunctionAttributes.h>

struct StylePropertySymbolMap final {
    [[nodiscard]] [[NOINLINE]] constexpr cs2::CStyleSymbol findSymbol(const char* stylePropertyName) const noexcept final
    {
        if (!symbols)
            return {};

        for (int i = 0; i < symbols->numElements - 1; ++i) {
            if (std::strcmp(symbols->memory[i].key.m_pString, stylePropertyName) == 0)
                return symbols->memory[i].value;
        }
        return {};
    }

    const cs2::CPanelStyle::StylePropertySymbols* restrict symbols;
};
