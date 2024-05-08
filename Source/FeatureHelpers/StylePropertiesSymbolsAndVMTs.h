#pragma once

#include <array>
#include <concepts>
#include <type_traits>

#include <CS2/Classes/Panorama.h>
#include <Platform/VmtFinder.h>
#include <Utils/TypeIndex.h>

#include "StylePropertySymbolMap.h"

template <typename... StyleProperties>
requires (std::is_base_of_v<cs2::CStyleProperty, StyleProperties> && ...)
struct StylePropertiesSymbolsAndVMTsBase {
    StylePropertiesSymbolsAndVMTsBase(StylePropertySymbolMap symbolMap, const VmtFinder& panoramaVmtFinder) noexcept
        : symbols{symbolMap.findSymbol(StyleProperties::kName)...}
        , vmts{panoramaVmtFinder.findVmt(StyleProperties::kMangledTypeName)...}
    {
        static_assert(sizeof...(StyleProperties) == symbols.size(), "Number of StyleProperties must match the size of symbols array");
        static_assert(sizeof...(StyleProperties) == vmts.size(), "Number of StyleProperties must match the size of vmts array");
    }

    const cs2::CStyleSymbol getSymbol() const noexcept requires std::is_same_v<StyleProperties, StyleProperty>
    {
        return symbols[utils::typeIndex<StyleProperty, std::tuple<StyleProperties...>>()];
    }

    const void* getVmt() const noexcept requires std::is_same_v<StyleProperties, StyleProperty>
    {
        return vmts[utils::typeIndex<StyleProperty, std::tuple<StyleProperties...>>()];
    }

private:
    std::array<cs2::CStyleSymbol, sizeof...(StyleProperties)> symbols;
    std::array<const void*, sizeof...(StyleProperties)> vmts;
};

using StylePropertiesSymbolsAndVMTs =
    StylePropertiesSymbolsAndVMTsBase<
        cs2::CStylePropertyWidth,
        cs2::CStylePropertyOpacity,
        cs2::CStylePropertyZIndex,
        cs2::CStylePropertyHeight,
        cs2::CStylePropertyImageShadow,
        cs2::CStylePropertyPosition,
        cs2::CStylePropertyTransformOrigin,
        cs2::CStylePropertyAlign,
        cs2::CStylePropertyWashColor,
        cs2::CStylePropertyFlowChildren,
        cs2::CStylePropertyFont,
        cs2::CStylePropertyTextShadow,
        cs2::CStylePropertyMargin>;
