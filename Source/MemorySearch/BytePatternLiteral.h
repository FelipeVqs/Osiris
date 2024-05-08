#pragma once

#include "BytePatternStorage.h"
#include "BytePatternView.h"
#include "PatternStringWildcard.h"

template <BytePatternStorage Storage>
using BytePatternViewType = BytePatternView<Storage.size>;

template <BytePatternStorage Storage>
auto operator"" _pat()
{
    constexpr std::array<char, Storage.size> pattern{[]{
        constexpr std::array<char, Storage.size> truncatedPattern;
        std::copy_n(Storage.pattern.begin(), Storage.size, truncatedPattern.begin());
        return truncatedPattern;
    }()};

    return BytePatternViewType<Storage>{pattern};
}
