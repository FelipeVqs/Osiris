#ifndef BYTE_PATTERN_STORAGE_TEST_H
#define BYTE_PATTERN_STORAGE_TEST_H

#include <gtest/gtest.h>
#include <MemorySearch/BytePatternStorage.h>

namespace
{
using BytePattern = MemorySearch::BytePatternStorage;
using BytePatternView = std::string_view;

BytePatternView asBytePatternView(const BytePattern& pattern)
{
    return BytePatternView{ pattern.pattern.data(), pattern.size };
}

}  // namespace

TEST(BytePatternStorageTest, StorageHasSizeEqualToLengthOfConvertedPattern)
{
    constexpr BytePattern storage{ "83 EC ? ? 4C ? 80 3D" };
    EXPECT_EQ(storage.size, 8);
}

TEST(BytePatternStorageTest, PatternConversionIsPerformedInConstructor)
{
    constexpr BytePattern storage{ "E8 ? ? ? ? 48 00 C0 74 62" };
    constexpr BytePatternView expectedPattern = "\xE8????\x48\x00\xC0\x74\x62"sv;
    const auto actualPattern = asBytePatternView(storage);
    EXPECT_EQ(actualPattern, expectedPattern);
}

TEST(BytePatternStorageTest, PatternConversionCorrectlyEscapesBackslashes)
{
    constexpr BytePattern storage{ "E8 \\? \\? \\? \\? 48 00 C0 74 62" };
    constexpr BytePatternView expectedPattern = "\xE8\\?\\?\\?\\?\x48\x00\xC0\x74\x62"sv;
    const auto actualPattern = asBytePatternView(storage);
    EXPECT_EQ(actualPattern, expectedPattern);
}

#endif // BYTE_PATTERN_STORAGE_TEST_H
