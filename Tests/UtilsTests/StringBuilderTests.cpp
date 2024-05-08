#ifndef UTILS_STRINGBUILDER_H
#define UTILS_STRINGBUILDER_H

#include <array>
#include <cstring>
#include <functional>
#include <memory>
#include <string_view>

namespace Utils
{

class StringBuilder
{
public:
    explicit StringBuilder(std::array<char, 30>& buffer);

    StringBuilder& put(char c);
    StringBuilder& put(std::string_view str);
    StringBuilder& putHex(unsigned int value);
    StringBuilder& put(const std::function<void(StringBuilder&)>& invocable);

    std::string_view string() const noexcept;
    const char* cstring() const noexcept;

private:
    std::array<char, 30>& buffer;
};

}  // namespace Utils

#endif  // UTILS_STRINGBUILDER_H


#include "StringBuilder.h"

namespace Utils
{

StringBuilder::StringBuilder(std::array<char, 30>& buffer)
    : buffer(buffer)
{
    buffer[29] = '\0';
}

StringBuilder& StringBuilder::put(char c)
{
    buffer[0] = c;
    return *this;
}

StringBuilder& StringBuilder::put(std::string_view str)
{
    std::copy_n(str.data(), std::min(str.size(), buffer.size() - 1), buffer.data());
    buffer[buffer.size() - 1] = '\0';
    return *this;
}

StringBuilder& StringBuilder::putHex(unsigned int value)
{
    char buffer[9];
    snprintf(buffer, sizeof(buffer), "%x", value);
    return put(std::string_view(buffer, strlen(buffer)));
}

StringBuilder& StringBuilder::put(const std::function<void(StringBuilder&)>& invocable)
{
    invocable(*this);
    return *this;
}

std::string_view StringBuilder::string() const noexcept
{
    return std::string_view(buffer.data(), buffer.size());
}

const char* StringBuilder::cstring() const noexcept
{
    return buffer.data();
}

}  // namespace Utils


#include <algorithm>
#include <memory>
#include <string_view>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Utils/StringBuilder.h"

namespace
{

class TestStringBuilder : public testing::Test {
protected:
    [[nodiscard]] auto bufferString() const noexcept
    {
        return std::string_view{ std::begin(buffer), std::end(buffer) };
    }

    void putIntoBuffer(std::string_view str)
    {
        std::copy_n(str.data(), (std::min)(str.size(), sizeof(buffer)), &buffer[0]);
    }

    char buffer[30]{};
    Utils::StringBuilder builder{ buffer };
};

TEST_F(TestStringBuilder, StringIsFormattedIntoProvidedBuffer)
{
    builder.put('a', " first ", 1234, [](Utils::StringBuilder& builder) { builder.put(567); }, " end");
    EXPECT_TRUE(bufferString().starts_with("a first 1234567 end"));
}

TEST_F(TestStringBuilder, PutMethodReturnsReferenceToSelf)
{
    decltype(auto) result = builder.put("str");
    EXPECT_EQ(std::addressof(result), std::addressof(builder));
}

TEST_F(TestStringBuilder, PutHexMethodReturnsReferenceToSelf)
{
    decltype(auto) result = builder.putHex(0x123);
    EXPECT_EQ(std::addressof(result), std::addressof(builder));
}

TEST_F(TestStringBuilder, StringViewWithCanBeRetrieved)
{
    builder.put("some string ").putHex(0xc0de);
    const auto string = builder.string();
    EXPECT_EQ(string.data(), &buffer[0]);
    EXPECT_EQ(string, "some string c0de");
}

TEST_F(TestStringBuilder, NullTerminatedCstringCanBeRetrieved)
{
    putIntoBuffer("abcdef");
    builder.put("str");
    const auto cstring = builder.cstring();
    EXPECT_EQ(cstring, &buffer[0]);
    EXPECT_STREQ(cstring, "str");
}

TEST_F(TestStringBuilder, EmptyStringViewIsReturnedWhenNothingWasWritten)
{
    const auto string = builder.string();
    EXPECT_EQ(string.data(), &buffer[0]);
    EXPECT_TRUE(string.empty());
}

TEST_F(TestStringBuilder, EmptyNullTerminatedCstringIsReturnedWhenNothingWasWritten)
{
    const auto cstring = builder.cstring();
    EXPECT_EQ(cstring, &buffer[0]);
    EXPECT_EQ(cstring[0], '\0');
}

TEST_F(TestStringBuilder, StringCanBeWritten)
{
    builder.put("one").put("two").put("three");
    EXPECT_EQ(builder.string(), "onetwothree");
}

TEST_F(TestStringBuilder, CharCanBeWritten)
{
    builder.put('x').put('y').put('z');
    EXPECT_EQ(builder.string(), "xyz");
}

TEST_F(TestStringBuilder, IntegerCanBeWrittenAsDecimal)
{
    builder.put(123).put(456).put(777);
    EXPECT_EQ(builder.string(), "123456777");
}

TEST_F(TestStringBuilder, IntegerCanBeWrittenAsHexadecimal)
{
    builder.putHex(0xc).putHex(0xabcdef0123456789);
    EXPECT_EQ(builder.string(), "cabcdef0123456789");
}

TEST_F(TestStringBuilder, PutAcceptsInvocable)
{
    testing::MockFunction<void(Utils::StringBuilder& builder)> mockInvocable;
    EXPECT_CALL(mockInvocable, Call(testing::Ref(builder))).WillOnce(testing::Invoke(
        [](Utils::StringBuilder& builder) { builder.put("123"); }
    ));
    builder.put(mockInvocable.AsStdFunction());
    EXPECT_EQ(builder.string(), "123");
}

}  // namespace
