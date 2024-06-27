#include "objects/packages/packages.hpp"

#include <gtest/gtest.h>

namespace {

using namespace liblockfile;

TEST(PackagesTest, DefaultPackagesAreEmpty) {
    EXPECT_EQ(0, Packages().get().size());
}

TEST(PackagesTest, DefaultPackagesByAnyArchAreEmpty) {
    EXPECT_EQ(0, Packages().get_by_arch("arch").size());
    EXPECT_EQ(0, Packages().get_by_arch("x86_64").size());
    EXPECT_EQ(0, Packages().get_by_arch("any").size());
}

}