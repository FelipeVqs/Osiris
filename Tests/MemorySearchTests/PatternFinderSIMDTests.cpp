#ifndef BYTE_PATTERN_LITERAL_H
#define BYTE_PATTERN_LITERAL_H

#include <cstring>
#include <string>

class BytePattern {
public:
    explicit BytePattern(const std::string& pattern) {
        const size_t patternLength = pattern.length();
        if (patternLength % 2 != 0) {
            // Pattern must have an even number of digits
            // (each digit represents a nibble)
            return;
        }

        data_ = new std::byte[patternLength / 2];
        std::memset(data_, 0, patternLength / 2);

        for (size_t i = 0; i < patternLength; i += 2) {
            const char highNibble = pattern[i];
            const char lowNibble = pattern[i + 1];

            if (highNibble < '0' || (highNibble > '9' && highNibble < 'A') || highNibble > 'F' ||
                lowNibble < '0' || (lowNibble > '9' && lowNibble < 'A') || lowNibble > 'F') {
                // Invalid nibble value
                return;
            }

            const int highNibbleValue = (highNibble <= '9') ? (highNibble - '0') * 16 : (highNibble - 'A' + 10) * 16;
            const int lowNibbleValue = (lowNibble <= '9') ? lowNibble - '0' : lowNibble - 'A' + 10;
            data_[i / 2] = static_cast<std::byte>(highNibbleValue | lowNibbleValue);
        }

        size_ = patternLength / 2;
    }

    ~BytePattern() {
        delete[] data_;
    }

    const std::byte* data() const {
        return data_;
    }

    size_t size() const {
        return size_;
    }

private:
    std::byte* data_;
    size_t size_;
};

#endif // BYTE_PATTERN_LITERAL_H

// ... (other headers and code)

#include "BytePatternLiteral.h"

namespace
{

constexpr BytePattern dummyPattern{"\\xAA\\BB"};

TEST(PatternFinderSIMD_NoBytesTest_NotCheckedBytesAreEmptySpan, PatternFinderSIMD_NoBytesTest) {
    PatternFinderSIMD finder{ {}, dummyPattern };
    EXPECT_TRUE(finder.getNotCheckedBytes().empty());
}

TEST(PatternFinderSIMD_NoBytesTest_FinderReturnsNullptr, PatternFinderSIMD_NoBytesTest) {
    PatternFinderSIMD finder{ {}, dummyPattern };
    EXPECT_EQ(finder(), nullptr);
}

TEST(PatternFinderSIMDTest_NoBytesAreCheckedUntilFinderIsInvoked, PatternFinderSIMDTest) {
    std::array<std::byte, 1000> bytes{};
    PatternFinderSIMD finder{bytes, BytePattern{"\\xAA"}};
    const auto notCheckedBytes = finder.getNotCheckedBytes();
    ASSERT_EQ(notCheckedBytes.size(), bytes.size());
    EXPECT_EQ(&notCheckedBytes.front(), &bytes.front());
    EXPECT_EQ(&notCheckedBytes.back(), &bytes.back());
}

TEST(PatternFinderSIMDTest_OneBytePatternCanBeMatched, PatternFinderSIMDTest) {
    std::array<std::byte, 64> bytes{};
    bytes[20] = std::byte{ 0x12 };

    PatternFinderSIMD finder{bytes, BytePattern{"\\x12"}};
    EXPECT_EQ(finder(), &bytes[20]);
}

// ... (other tests)

}
