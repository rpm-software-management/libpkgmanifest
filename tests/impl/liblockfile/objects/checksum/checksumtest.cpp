#include "liblockfile/objects/checksum/checksum.hpp"

#include <gtest/gtest.h>

namespace {

using namespace liblockfile::internal;

TEST(ChecksumTest, DefaultMethodIsSHA256) {
    EXPECT_EQ(liblockfile::ChecksumMethod::SHA256, Checksum().get_method());
}

TEST(ChecksumTest, DefaultDigestIsEmpty) {
    EXPECT_EQ(std::string(), Checksum().get_digest());
}

TEST(ChecksumTest, SetMethodIsReturned) {
    Checksum checksum;
    checksum.set_method(liblockfile::ChecksumMethod::MD5);
    EXPECT_EQ(liblockfile::ChecksumMethod::MD5, checksum.get_method());
}

TEST(ChecksumTest, SetDigestIsReturned) {
    Checksum checksum;
    checksum.set_digest("abcd");
    EXPECT_EQ("abcd", checksum.get_digest());
}

}