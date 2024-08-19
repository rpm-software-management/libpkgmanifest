#include "liblockfile/objects/version/version.hpp"

#include <gtest/gtest.h>

namespace {

using namespace liblockfile::internal;

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

TEST(VersionTest, ClonedObjectHasSameValuesAsOriginal) {
    Version version;
    version.set_major(5);
    version.set_minor(7);
    version.set_patch(9);

    auto clone(version.clone());
    EXPECT_EQ(version.get_major(), clone->get_major());
    EXPECT_EQ(version.get_minor(), clone->get_minor());
    EXPECT_EQ(version.get_patch(), clone->get_patch());
}

}