#pragma once

#include <cctype>
#include <charconv>
#include <string_view>
#include <concepts>

class StringParser {
public:
    explicit StringParser(const char* string) noexcept
        : string_{ string }
    {
    }

    StringParser(StringParser&& other) noexcept
        : string_{ other.string_ }
    {
        other.string_ = nullptr;
    }

    StringParser& operator=(StringParser&& other) noexcept
    {
        if (this != &other) {
            string_ = other.string_;
            other.string_ = nullptr;
        }
        return *this;
    }

    [[nodiscard]] const char* begin() const noexcept { return string_; }
    [[nodiscard]] const char* end() const noexcept { return string_ + length_; }

    [[nodiscard]] std::string_view getLine(char delimiter) noexcept
    {
        const auto begin = string_;
        std::size_t length = 0;
        while (*string_ != '\0' && *string_++ != delimiter)
            ++length;
        return { begin, length };
    }

    [[nodiscard]] char getChar() noexcept
    {
        if (*string_ != '\0')
            return *string_++;
        return '\0';
    }

    [[nodiscard]] char peekChar() const noexcept
    {
        if (*string_ != '\0')
            return *string_;
        return '\0';
    }

    template <std::integral IntegralType>
    bool parseInt(IntegralType& result) noexcept
    {
        static_assert(std::is_unsigned_v<IntegralType>);

        IntegralType parsedInteger{};
        bool parseSuccessful = false;

        std::size_t currentDigit = 0;
        while (*string_ >= '0' && *string_ <= '9') {
            if (currentDigit < std::numeric_limits<IntegralType>::digits10) {
                parsedInteger *= 10;
                parsedInteger += (*string_ - '0');
                ++currentDigit;
                parseSuccessful = true;
            } else {
                parseSuccessful = false;
            }

            ++string_;
        }

        if (parseSuccessful)
            result = parsedInteger;

        return parseSuccessful;
    }

    template <std::floating_point FloatType>
    bool parseFloat(FloatType& result) noexcept
    {
        FloatType parsedFloat{};
        bool parseSuccessful = false;

        if (*string_ == '-') {
            ++string_;
            if (*string_ < '0' || *string_ > '9')
                return false;
        }

        while (*string_ >= '0' && *string_ <= '9') {
            parsedFloat *= 10.0f;
            parsedFloat += static_cast<FloatType>(*string_ - '0');
            parseSuccessful = true;
            ++string_;
        }

        if (*string_ == '.') {
            ++string_;
            FloatType fraction = 1.0f;
            while (*string_ >= '0' && *string_ <= '9') {
                fraction /= 10.0f;
                parsedFloat += static_cast<FloatType>(*string_ - '0') * fraction;
                parseSuccessful = true;
                ++string_;
            }
        }

        if (*string_ == 'e' || *string_ == 'E') {
            ++string_;
            int exponent = 0;
            bool exponent_is_negative = false;
            if (*string_ == '-') {
                exponent_is_negative = true;
                ++string_;
            } else if (*string_ == '+') {
                ++string_;
            }
            while (*string_ >= '0' && *string_ <= '9') {
                exponent = 10 * exponent + (*string_ - '0');
                ++string_;
            }
            if (exponent_is_negative)
                parsedFloat /= std::pow(10.0f, exponent);
            else
                parsedFloat *= std::pow(10.0f, exponent);
        }

        if (parseSuccessful)
            result = parsedFloat;

        return parseSuccessful;
    }

private:
    const char* string_;
    std::size_t length_ = 0;
};
