#include <string_view>
#include <type_traits>

#include <gtest/gtest.h>

#include <MemorySearch/BytePatternLiteral.h>
#include <MemorySearch/BytePatternStorage.h>

namespace
{

using namespace std::string_view_literals;
using namespace MemorySearch::Literals;

inline static void BytePatternLiteralTest_LiteralReturnsConvertedPattern() {
    constexpr auto expectedPattern = "\x00\x11\x22\x33\xAA\xBB\xCC"sv;

    const auto patternView = "00 11 22 33 AA BB CC"_pat;
    const auto actualPattern = std::string_view{patternView.data(), patternView.size()};
    EXPECT_EQ(actualPattern, expectedPattern);
}

}  // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
