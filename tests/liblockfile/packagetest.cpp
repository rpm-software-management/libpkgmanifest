#include "objects/package/package.hpp"

#include "ichecksummock.hpp"

#include <gtest/gtest.h>

namespace {

using namespace liblockfile;

using ::testing::NiceMock;

TEST(PackageTest, DefaultArchIsEmpty) {
    EXPECT_EQ(std::string(), Package().get_arch());
}

TEST(PackageTest, DefaultRepoIdIsEmpty) {
    EXPECT_EQ(std::string(), Package().get_repo_id());
}

TEST(PackageTest, DefaultUrlIsEmpty) {
    EXPECT_EQ(std::string(), Package().get_url());
}

TEST(PackageTest, DefaultChecksumIsNull) {
    EXPECT_EQ(nullptr, &Package().get_checksum());
}

TEST(PackageTest, DefaultSizeIsZero) {
    EXPECT_EQ(0, Package().get_size());
}

TEST(PackageTest, DefaultNevraIsEmpty) {
    EXPECT_EQ(std::string(), Package().get_nevra());
}

TEST(PackageTest, DefaultSrpmIsEmpty) {
    EXPECT_EQ(std::string(), Package().get_srpm());
}

TEST(PackageTest, SetArchIsReturned) {
    Package package;
    package.set_arch("aarch64");
    EXPECT_EQ("aarch64", package.get_arch());
}

TEST(PackageTest, SetRepoIdIsReturned) {
    Package package;
    package.set_repo_id("repo1");
    EXPECT_EQ("repo1", package.get_repo_id());
}

TEST(PackageTest, SetUrlIsReturned) {
    Package package;
    package.set_url("url");
    EXPECT_EQ("url", package.get_url());
}

TEST(PackageTest, SetChecksumObjectIsReturned) {
    auto checksum = std::make_unique<NiceMock<ChecksumMock>>();
    auto checksum_ptr = checksum.get();

    Package package;
    package.set_checksum(std::move(checksum));

    EXPECT_EQ(checksum_ptr, &package.get_checksum());
}

TEST(PackageTest, SetSizeIsReturned) {
    Package package;
    package.set_size(5678U);
    EXPECT_EQ(5678U, package.get_size());
}

TEST(PackageTest, SetNevraIsReturned) {
    Package package;
    package.set_nevra("nevra");
    EXPECT_EQ("nevra", package.get_nevra());
}

TEST(PackageTest, SetSrpmIsReturned) {
    Package package;
    package.set_srpm("srpm");
    EXPECT_EQ("srpm", package.get_srpm());
}

}