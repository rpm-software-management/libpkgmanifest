#include "objects/version/version.hpp"

#include <gtest/gtest.h>

namespace {

using namespace liblockfile;

TEST(VersionTest, DefaultMajorIsZero) {
    EXPECT_EQ(0, Version().get_major());
}

TEST(VersionTest, DefaultMinorIsZero) {
    EXPECT_EQ(0, Version().get_minor());
}

TEST(VersionTest, DefaultPatchIsZero) {
    EXPECT_EQ(0, Version().get_patch());
}

TEST(VersionTest, SetMajorIsReturned) {
    Version version;
    version.set_major(3);
    EXPECT_EQ(3, version.get_major());
}

TEST(VersionTest, SetMinorIsReturned) {
    Version version;
    version.set_minor(6);
    EXPECT_EQ(6, version.get_minor());
}

TEST(VersionTest, SetPatchIsReturned) {
    Version version;
    version.set_patch(1);
    EXPECT_EQ(1, version.get_patch());
}

}