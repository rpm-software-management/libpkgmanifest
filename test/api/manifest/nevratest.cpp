#include "libpkgmanifest/manifest/nevra.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::manifest;

TEST(ApiNevraTest, SetName) {
    Nevra nevra;
    nevra.set_name("package1");
    EXPECT_EQ(nevra.get_name(), "package1");
}

TEST(ApiNevraTest, SetEpoch) {
    Nevra nevra;
    nevra.set_epoch("1");
    EXPECT_EQ(nevra.get_epoch(), "1");
}

TEST(ApiNevraTest, SetVersion) {
    Nevra nevra;
    nevra.set_version("1.2.3");
    EXPECT_EQ(nevra.get_version(), "1.2.3");
}

TEST(ApiNevraTest, SetRelease) {
    Nevra nevra;
    nevra.set_release("1.fc34");
    EXPECT_EQ(nevra.get_release(), "1.fc34");
}

TEST(ApiNevraTest, SetArch) {
    Nevra nevra;
    nevra.set_arch("x86_64");
    EXPECT_EQ(nevra.get_arch(), "x86_64");
}

TEST(ApiNevraTest, CopyConstructorCreatesIndependentCopy) {
    Nevra nevra;
    nevra.set_name("package1");

    Nevra copied_nevra(nevra);
    EXPECT_EQ(copied_nevra.get_name(), "package1");
    copied_nevra.set_name("package2");
    EXPECT_EQ(nevra.get_name(), "package1");
}

TEST(ApiNevraTest, CopyAssignmentCreatesIndependentCopy) {
    Nevra nevra;
    nevra.set_name("package1");

    Nevra copied_nevra;
    copied_nevra = nevra;
    EXPECT_EQ(copied_nevra.get_name(), "package1");
    copied_nevra.set_name("package2");
    EXPECT_EQ(nevra.get_name(), "package1");
}

TEST(ApiNevraTest, MoveConstructorTransfersOwnership) {
    Nevra nevra;
    nevra.set_name("package1");

    Nevra moved_nevra(std::move(nevra));
    EXPECT_EQ(moved_nevra.get_name(), "package1");
}

TEST(ApiNevraTest, MoveAssignmentTransfersOwnership) {
    Nevra nevra;
    nevra.set_name("package1");

    Nevra moved_nevra;
    moved_nevra = std::move(nevra);
    EXPECT_EQ(moved_nevra.get_name(), "package1");
}

}