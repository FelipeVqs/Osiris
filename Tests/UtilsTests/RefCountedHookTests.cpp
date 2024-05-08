#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <Utils/RefCountedHook.h>

namespace
{

struct MockHook : RefCountedHook<MockHook> {
    MOCK_METHOD(bool, isInstalled, (), (const noexcept) = 0);
    MOCK_METHOD(void, install, (), (noexcept) = 0);
    MOCK_METHOD(void, uninstall, (), (noexcept) = 0);
};

class RefCountedHookTest : public testing::Test {
protected:
    testing::StrictMock<MockHook> hook;

    void SetUp() override { hook.incrementReferenceCount(); }
    void TearDown() override { hook.decrementReferenceCount(); }
};

TEST_F(RefCountedHookTest, WillBeInstalledIfReferenced) {
    hook.incrementReferenceCount();
    hook.update();

    EXPECT_CALL(hook, isInstalled()).WillOnce(Return(false));
    EXPECT_CALL(hook, install());
    hook.update();
}

TEST_F(RefCountedHookTest, WillNotBeInstalledIfNotReferenced) {
    hook.update();

    EXPECT_CALL(hook, isInstalled()).WillOnce(Return(false));
    EXPECT_CALL(hook, install()).Times(0);
    hook.update();
}

TEST_F(RefCountedHookTest, WillBeUninstalledIfNotReferenced) {
    hook.update();

    EXPECT_CALL(hook, isInstalled()).WillOnce(Return(true));
    EXPECT_CALL(hook, uninstall());
    hook.update();
}

TEST_F(RefCountedHookTest, WillNotBeUninstalledIfReferenced) {
    hook.incrementReferenceCount();
    hook.update();

    EXPECT_CALL(hook, isInstalled()).WillOnce(Return(true));
    EXPECT_CALL(hook, uninstall()).Times(0);
    hook.update();
}

TEST_F(RefCountedHookTest, WillBeForceUninstalledWhenInstalled) {
    hook.install();

    EXPECT_CALL(hook, isInstalled()).WillOnce(Return(true));
    EXPECT_CALL(hook, uninstall());
    hook.forceUninstall();
}

TEST_F(RefCountedHookTest, WillNotBeForceUninstalledWhenNotInstalled) {
    EXPECT_CALL(hook, isInstalled()).WillOnce(Return(false));
    EXPECT_CALL(hook, uninstall()).Times(0);
    hook.forceUninstall();
}

}  // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
