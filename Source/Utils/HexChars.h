#pragma once

#include <array>
#include <cstdint>
#include <optional>

[[nodiscard]] constexpr std::uint8_t hexDigitToDecimal(char hexDigit) noexcept
{
    if (hexDigit >= '0' && hexDigit <= '9')
        return hexDigit - '0';
    if (hexDigit >= 'A' && hexDigit <= 'F')
        return hexDigit - 'A' + 10;
    if (hexDigit >= 'a' && hexDigit <= 'f')
        return hexDigit - 'a' + 10;
    return 0xFF; // return 0xFF for invalid hex digits
}

[[nodiscard]] constexpr bool isValidOneDigitHexNumber(std::uint8_t number) noexcept
{
    return (number & 0xF0) == 0;
}

constexpr std::size_t hexCharsInByte = 2;

[[nodiscard]] constexpr std::optional<std::uint8_t> hexCharsToByte(const std::array<char, hexCharsInByte>& chars)
{
    const auto highFourBits = hexDigitToDecimal(chars[0]);
    const auto lowFourBits = hexDigitToDecimal(chars[1]);

    if (isValidOneDigitHexNumber(highFourBits) && isValidOneDigitHexNumber(lowFourBits))
        return static_cast<std::uint8_t>(highFourBits << 4 | lowFourBits);
    return {};
}

// Example usage
int main()
{
    const std::array<char, hexCharsInByte> hexChars{'A', 'F'};
    if (const auto byte = hexCharsToByte(hexChars); byte.has_value())
    {
        std::uint8_t result = *byte;
        // Do something with the result
    }
    else
    {
        // Handle invalid hex characters or error
    }
    return 0;
}
