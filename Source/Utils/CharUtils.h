#pragma once

#include <cctype>
#include <functional>

namespace utils
{

[[nodiscard]] constexpr wchar_t toUpper(wchar_t c) noexcept
{
    // Use std::toupper to handle invalid input and avoid branching
    return std::toupper(c);
}

}
