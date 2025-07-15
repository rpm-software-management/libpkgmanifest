// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "libpkgmanifest/common/version.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::common;

TEST(ApiVersionTest, SetMajor) {
    Version version;
    version.set_major(5);
    EXPECT_EQ(version.get_major(), 5);
}

TEST(ApiVersionTest, SetMinor) {
    Version version;
    version.set_minor(2);
    EXPECT_EQ(version.get_minor(), 2);
}

TEST(ApiVersionTest, SetPatch) {
    Version version;
    version.set_patch(9);
    EXPECT_EQ(version.get_patch(), 9);
}

TEST(ApiVersionTest, CopyConstructorCreatesIndependentCopy) {
    Version version;
    version.set_major(5);

    Version copied_version(version);
    EXPECT_EQ(copied_version.get_major(), 5);
    copied_version.set_major(10);
    EXPECT_EQ(version.get_major(), 5);
}

TEST(ApiVersionTest, CopyAssignmentCreatesIndependentCopy) {
    Version version;
    version.set_major(5);

    Version copied_version;
    copied_version = version;
    EXPECT_EQ(copied_version.get_major(), 5);
    copied_version.set_major(10);
    EXPECT_EQ(version.get_major(), 5);
}

TEST(ApiVersionTest, MoveConstructorTransfersOwnership) {
    Version version;
    version.set_major(5);

    Version moved_version(std::move(version));
    EXPECT_EQ(moved_version.get_major(), 5);
}

TEST(ApiVersionTest, MoveAssignmentTransfersOwnership) {
    Version version;
    version.set_major(5);

    Version moved_version;
    moved_version = std::move(version);
    EXPECT_EQ(moved_version.get_major(), 5);
}

}