#ifndef TEST_PATTERN_SEARCH_RESULT_H
#define TEST_PATTERN_SEARCH_RESULT_H

#include <array>
#include <cstring>
#include <gtest/gtest.h>
#include <memorysearch/patternsearchresult.h>

#endif //TEST_PATTERN_SEARCH_RESULT_H

namespace {

class PatternSearchResultTest : public testing::Test {
protected:
    std::array<std::byte, 60> foundPatternMemory;
};

class PatternSearchResultDefaultConstructedTest : public PatternSearchResultTest {
protected:
    PatternSearchResult sut;
};

TEST_F(PatternSearchResultDefaultConstructedTest, HasNullPointer) {
    EXPECT_EQ(sut.as<void*>(), nullptr);
}

TEST_F(PatternSearchResultDefaultConstructedTest, AddMethodDoesNothing) {
    EXPECT_EQ(sut.add(5).as<void*>(), nullptr);
}

TEST_F(PatternSearchResultDefaultConstructedTest, AbsMethodReturnsNullPointer) {
    EXPECT_EQ(sut.add(7).abs().as<void*>(), nullptr);
}

class PatternSearchResultToAbsoluteTest : public PatternSearchResultTest, public testing::WithParamInterface<std::tuple<std::size_t, std::int32_t>> {
protected:
    static constexpr auto kRuntimeMemoryOffset{3};

    PatternSearchResultToAbsoluteTest() noexcept
    {
        const auto relativeOffset{getRelativeOffset()};
        std::memcpy(foundPatternMemory.data(), &relativeOffset, sizeof(relativeOffset));
    }

    [[nodiscard]] std::size_t getFoundPatternOffset() const noexcept
    {
        return std::get<0>(GetParam());
    }

    [[nodiscard]] std::int32_t getRelativeOffset() const noexcept
    {
        return std::get<1>(GetParam());
    }

    [[nodiscard]] PatternSearchResult patternSearchResult() const noexcept
    {
        return PatternSearchResult{nullptr, getFoundPatternOffset(), foundPatternMemory};
    }
};

TEST_F(PatternSearchResultToAbsoluteTest, ToAbsoluteReturnsCorrectAddress) {
    const auto absoluteAddress{patternSearchResult().getAbsoluteAddress()};
    const auto expectedAddress{&runtimeMemory.at(kRuntimeMemoryOffset + getFoundPatternOffset() + sizeof(std::int32_t) + getRelativeOffset())};
    EXPECT_EQ(absoluteAddress, expectedAddress);
}

INSTANTIATE_TEST_SUITE_P(, PatternSearchResultToAbsoluteTest,
    testing::Combine(testing::Values(0, 1, 5), testing::Values(-5, 0, 7)));

} // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
