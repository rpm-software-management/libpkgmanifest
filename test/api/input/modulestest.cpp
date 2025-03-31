#include "libpkgmanifest/input/modules.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::input;

TEST(ApiModulesTest, AddEnables) {
    Modules modules;
    modules.get_enables().push_back("module1");
    modules.get_enables().push_back("module2");

    EXPECT_EQ(modules.get_enables().size(), 2);
    EXPECT_THAT(modules.get_enables(), ::testing::ElementsAre("module1", "module2"));
}

TEST(ApiModulesTest, AddDisables) {
    Modules modules;
    modules.get_disables().push_back("module1");
    modules.get_disables().push_back("module2");

    EXPECT_EQ(modules.get_disables().size(), 2);
    EXPECT_THAT(modules.get_disables(), ::testing::ElementsAre("module1", "module2"));
}

TEST(ApiModulesTest, CopyConstructorCreatesIndependentCopy) {
    Modules modules;
    modules.get_enables().push_back("module1");

    Modules copied_modules(modules);
    EXPECT_EQ(copied_modules.get_enables()[0], "module1");
    copied_modules.get_enables().push_back("module2");
    EXPECT_EQ(modules.get_enables().size(), 1);
    EXPECT_EQ(modules.get_enables()[0], "module1");
}

TEST(ApiModulesTest, CopyAssignmentCreatesIndependentCopy) {
    Modules modules;
    modules.get_enables().push_back("module1");

    Modules copied_modules;
    copied_modules = modules;
    EXPECT_EQ(copied_modules.get_enables()[0], "module1");
    copied_modules.get_enables().push_back("module2");
    EXPECT_EQ(modules.get_enables().size(), 1);
    EXPECT_EQ(modules.get_enables()[0], "module1");
}

TEST(ApiModulesTest, MoveConstructorTransfersOwnership) {
    Modules modules;
    modules.get_enables().push_back("module1");

    Modules moved_modules(std::move(modules));
    EXPECT_EQ(moved_modules.get_enables()[0], "module1");
}

TEST(ApiModulesTest, MoveAssignmentTransfersOwnership) {
    Modules modules;
    modules.get_enables().push_back("module1");

    Modules moved_modules;
    moved_modules = std::move(modules);
    EXPECT_EQ(moved_modules.get_enables()[0], "module1");
}

}