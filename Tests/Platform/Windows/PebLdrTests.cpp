#include <string>

#include <gtest/gtest.h>

#include "PebLdrBuilder.h"

namespace
{

class TestPebLdr : public testing::Test {
protected:
    void addDummyModule(void* handle, const std::string& dllName)
    {
        builder.addModule(handle, std::wstring(dllName.begin(), dllName.end()).c_str());
    }

    PebLdrBuilder builder;
};

TEST_F(TestPebLdr, NullHandleIsReturnedWhenModuleIsNotFound) {
    addDummyModule((void*)0x1234123412341234, "dllone");
    addDummyModule((void*)0x0BADC0DE0BADC0DE, "another.dll");
    EXPECT_EQ(builder.pebLdr().getModuleHandle("client.dll"), nullptr);
}

class TestPebLdr_Handle_Name : public TestPebLdr, public testing::WithParamInterface<std::tuple<void*, std::string>> {};

TEST_P(TestPebLdr_Handle_Name, ModuleCanBeFound) {
    const auto [handle, dllName] = GetParam();

    addDummyModule((void*)0xABABABABABABABAB, "dummy1.dll");
    addDummyModule((void*)0xCDCDCDCDCDCDCDCD, "dummy2.dll");
    addDummyModule(handle, dllName);

    EXPECT_EQ(builder.pebLdr().getModuleHandle(dllName), handle);
}

INSTANTIATE_TEST_SUITE_P(, TestPebLdr_Handle_Name, testing::Combine(
    testing::Values((void*)0xABABABABABABABAB, (void*)0xCDCDCDCDCDCDCDCD),
    testing::Values("client.dll", "engine.dll")
));

}
