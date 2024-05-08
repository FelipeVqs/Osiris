#include <utility>

#include <gtest/gtest.h>

#include <Utils/ReturnAddress.h>

namespace
{

using PairType = std::pair<void*, void*>;

class ReturnAddressTest : public testing::TestWithParam<PairType> {};

TEST_P(ReturnAddressTest, SameReturnAddressesCompareEqual) {
    EXPECT_EQ(ReturnAddress{GetParam().first}, ReturnAddress{GetParam().first});
}

TEST_P(ReturnAddressTest, DifferentReturnAddressesDoNotCompareEqual) {
    EXPECT_NE(ReturnAddress{GetParam().first}, ReturnAddress{GetParam().second});
    EXPECT_NE(ReturnAddress{GetParam().second}, ReturnAddress{GetParam().first});
}

INSTANTIATE_TEST_SUITE_P(ReturnAddressTestSuite, ReturnAddressTest, testing::ValuesIn(std::initializer_list<PairType>{
    {nullptr, reinterpret_cast<void*>(1234)},
    {reinterpret_cast<void*>(2048), reinterpret_cast<void*>(-1)},
    {reinterpret_cast<void*>(-1), nullptr},
    {nullptr, nullptr}
}));

}
