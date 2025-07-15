// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "libpkgmanifest/input/packages.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::input;

TEST(ApiInputPackagesTest, AddInstalls) {
    Packages packages;
    packages.get_installs().push_back("pkg1");
    packages.get_installs().push_back("pkg2");

    EXPECT_EQ(packages.get_installs().size(), 2);
    EXPECT_THAT(packages.get_installs(), ::testing::ElementsAre("pkg1", "pkg2"));
}

TEST(ApiInputPackagesTest, AddReinstalls) {
    Packages packages;
    packages.get_reinstalls().push_back("pkg1");
    packages.get_reinstalls().push_back("pkg2");

    EXPECT_EQ(packages.get_reinstalls().size(), 2);
    EXPECT_THAT(packages.get_reinstalls(), ::testing::ElementsAre("pkg1", "pkg2"));
}

TEST(ApiInputPackagesTest, CopyConstructorCreatesIndependentCopy) {
    Packages packages;
    packages.get_installs().push_back("pkg1");

    Packages copied_packages(packages);
    EXPECT_EQ(copied_packages.get_installs()[0], "pkg1");
    copied_packages.get_installs().push_back("pkg2");
    EXPECT_EQ(packages.get_installs().size(), 1);
    EXPECT_EQ(packages.get_installs()[0], "pkg1");
}

TEST(ApiInputPackagesTest, CopyAssignmentCreatesIndependentCopy) {
    Packages packages;
    packages.get_installs().push_back("pkg1");

    Packages copied_packages;
    copied_packages = packages;
    EXPECT_EQ(copied_packages.get_installs()[0], "pkg1");
    copied_packages.get_installs().push_back("pkg2");
    EXPECT_EQ(packages.get_installs().size(), 1);
    EXPECT_EQ(packages.get_installs()[0], "pkg1");
}

TEST(ApiInputPackagesTest, MoveConstructorTransfersOwnership) {
    Packages packages;
    packages.get_installs().push_back("pkg1");

    Packages moved_packages(std::move(packages));
    EXPECT_EQ(moved_packages.get_installs()[0], "pkg1");
}

TEST(ApiInputPackagesTest, MoveAssignmentTransfersOwnership) {
    Packages packages;
    packages.get_installs().push_back("pkg1");

    Packages moved_packages;
    moved_packages = std::move(packages);
    EXPECT_EQ(moved_packages.get_installs()[0], "pkg1");
}

}