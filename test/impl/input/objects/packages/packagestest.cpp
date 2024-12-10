#include "impl/input/objects/packages/packages.hpp"

#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal::input;

TEST(InputPackagesTest, DefaultInstallsIsEmpty) {
    EXPECT_TRUE(Packages().get_installs().empty());
}

TEST(InputPackagesTest, DefaultReinstallsIsEmpty) {
    EXPECT_TRUE(Packages().get_reinstalls().empty());
}

TEST(InputPackagesTest, ClonedObjectHasSameValuesAsOriginal) {
    Packages packages;
    packages.get_installs().push_back("pkg1");
    packages.get_installs().push_back("pkg2");
    packages.get_installs().push_back("pkg3");
    packages.get_reinstalls().push_back("repkg1");
    packages.get_reinstalls().push_back("repkg2");

    auto clone(packages.clone());
    EXPECT_EQ(packages.get_installs(), clone->get_installs());
    EXPECT_EQ(packages.get_reinstalls(), clone->get_reinstalls());
}

}