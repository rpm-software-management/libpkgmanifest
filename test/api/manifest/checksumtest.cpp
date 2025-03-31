#include "libpkgmanifest/manifest/checksum.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::manifest;

TEST(ApiChecksumTest, SetMethod) {
    Checksum checksum;
    checksum.set_method(ChecksumMethod::SHA256);
    EXPECT_EQ(checksum.get_method(), ChecksumMethod::SHA256);
}

TEST(ApiChecksumTest, SetDigest) {
    Checksum checksum;
    checksum.set_digest("abcdef");
    EXPECT_EQ(checksum.get_digest(), "abcdef");
}

TEST(ApiChecksumTest, CopyConstructorCreatesIndependentCopy) {
    Checksum checksum;
    checksum.set_digest("abcdef");

    Checksum copied_checksum(checksum);
    EXPECT_EQ(copied_checksum.get_digest(), "abcdef");
    copied_checksum.set_digest("fedcba");
    EXPECT_EQ(checksum.get_digest(), "abcdef");
}

TEST(ApiChecksumTest, CopyAssignmentCreatesIndependentCopy) {
    Checksum checksum;
    checksum.set_digest("abcdef");

    Checksum copied_checksum;
    copied_checksum = checksum;
    EXPECT_EQ(copied_checksum.get_digest(), "abcdef");
    copied_checksum.set_digest("fedcba");
    EXPECT_EQ(checksum.get_digest(), "abcdef");
}

TEST(ApiChecksumTest, MoveConstructorTransfersOwnership) {
    Checksum checksum;
    checksum.set_digest("abcdef");

    Checksum moved_checksum(std::move(checksum));
    EXPECT_EQ(moved_checksum.get_digest(), "abcdef");
}

TEST(ApiChecksumTest, MoveAssignmentTransfersOwnership) {
    Checksum checksum;
    checksum.set_digest("abcdef");

    Checksum moved_checksum;
    moved_checksum = std::move(checksum);
    EXPECT_EQ(moved_checksum.get_digest(), "abcdef");
}

}