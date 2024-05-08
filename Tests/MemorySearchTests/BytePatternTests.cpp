#include <algorithm>
#include <array>
#include <string>
#include <string_view>

#include <gtest/gtest.h>

#include <MemorySearch/BytePattern.h>
#include <MemorySearch/PatternStringWildcard.h>

namespace
{

using namespace std::string_view_literals;

template <std::size_t N>
[[nodiscard]] constexpr auto createByteArray(const unsigned char(&bytes)[N])
{
    std::array<std::byte, N> arr;
    std::ranges::transform(bytes, arr.begin(), [](unsigned char c) { return std::byte{c}; });
    return arr;
}

// Add a type alias for the test fixture to improve readability
using BytePatternWithWildcardTestFixture = testing::TestWithParam<char>;

TEST_F(BytePatternWithWildcardTestFixture, PatternMatchesMemoryWhenBytesAreTheSame) {
    auto pattern = MakeBytePattern(std::string_view{"\xAB\xCD\xEF"}, GetParam());
    EXPECT_TRUE(pattern.matches(createByteArray({ 0xAB, 0xCD, 0xEF })));
}

TEST_F(BytePatternWithWildcardTestFixture, PatternDoesNotMatchMemoryWhenBytesAreDifferent) {
    auto pattern = MakeBytePattern(std::string_view{"\xAB\xCD\xAB"}, GetParam());
    EXPECT_FALSE(pattern.matches(createByteArray({ 0xAB, 0xCD, 0xEF })));
}

TEST_F(BytePatternWithWildcardTestFixture, NullCharsInPatternDoesNotTerminateComparison) {
    auto pattern = MakeBytePattern(std::string_view{"\xAB\x00\xEF\x00\x13"}, GetParam());
    EXPECT_FALSE(pattern.matches(createByteArray({ 0xAB, 0x00, 0xEF, 0x00, 0x12 })));
}

TEST_F(BytePatternWithWildcardTestFixture, BytesOnWildcardPositionsAreIgnored) {
    const auto wildcard = GetParam();
    auto pattern = std::string{"\xAB"} + wildcard + "\xEF" + wildcard + "\xFF";
    EXPECT_TRUE(MakeBytePattern(pattern, GetParam()).matches(createByteArray({ 0xAB, 0xCC, 0xEF, 0xDD, 0xFF })));
}

TEST_F(BytePatternWithWildcardTestFixture, WildcardCharInMemoryDoesNotMatchEveryPatternChar) {
    auto pattern = MakeBytePattern(std::string_view{"\xAB\xCC\xEF\xDD\xFF"}, GetParam());
    EXPECT_FALSE(pattern.matches(createByteArray({ 0xAB, static_cast<unsigned char>(GetParam()), 0xEF, static_cast<unsigned char>(GetParam()), 0xFF })));
}

// Instantiate the test suite with two wildcard characters
INSTANTIATE_TEST_SUITE_P(, BytePatternWithWildcardTestFixture, testing::Values('?', '.'));

// Helper function to create a BytePattern object
inline BytePattern MakeBytePattern(std::string_view pattern, char wildcard)
{
    return BytePattern{pattern, wildcard};
}

}  // namespace
