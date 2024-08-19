#include "liblockfile/parser.hpp"

#include <gtest/gtest.h>

namespace {

using namespace liblockfile;

TEST(ApiParserTest, ParseSimpleLockFile) {
    auto file_path = std::string(getenv("PROJECT_SOURCE_DIR")) + "/test/data/simple.yaml";

    Parser parser;
    auto lock_file = parser.parse(file_path);

    EXPECT_EQ("rpm-lockfile", lock_file.get_document());
    EXPECT_EQ(1, lock_file.get_version().get_major());
    EXPECT_EQ(2, lock_file.get_version().get_minor());
    EXPECT_EQ(3, lock_file.get_version().get_patch());

    auto packages = lock_file.get_packages().get();
    EXPECT_EQ(2, packages.size());
    EXPECT_EQ(2, packages["i686"].size());
    EXPECT_EQ(1, packages["src"].size());

    auto i686_packages = lock_file.get_packages().get("i686");
    EXPECT_EQ(2, i686_packages.size());

    auto src_packages = lock_file.get_packages().get("src");
    EXPECT_EQ(1, src_packages.size());

    auto & package1 = packages.at("i686")[0];
    EXPECT_EQ("i686", package1.get_arch());
    EXPECT_EQ("repo1", package1.get_repo_id());
    EXPECT_EQ("url1", package1.get_url());
    EXPECT_EQ(liblockfile::ChecksumMethod::SHA512, package1.get_checksum().get_method());
    EXPECT_EQ("abcdef", package1.get_checksum().get_digest());
    EXPECT_EQ(152384, package1.get_size());
    EXPECT_EQ("nevra1", package1.get_nevra());
    EXPECT_EQ("srpm1", package1.get_srpm());

    auto & package2 = packages.at("i686")[1];
    EXPECT_EQ("i686", package2.get_arch());
    EXPECT_EQ("repo2", package2.get_repo_id());
    EXPECT_EQ("url2", package2.get_url());
    EXPECT_EQ(liblockfile::ChecksumMethod::MD5, package2.get_checksum().get_method());
    EXPECT_EQ("fedcba", package2.get_checksum().get_digest());
    EXPECT_EQ(378124894, package2.get_size());
    EXPECT_EQ("nevra2", package2.get_nevra());
    EXPECT_EQ("srpm2", package2.get_srpm());

    auto & package3 = packages.at("src")[0];
    EXPECT_EQ("src", package3.get_arch());
    EXPECT_EQ("repo3", package3.get_repo_id());
    EXPECT_EQ("http://some.server.org/folder/nevra3.rpm", package3.get_url());
    EXPECT_EQ(liblockfile::ChecksumMethod::SHA256, package3.get_checksum().get_method());
    EXPECT_EQ("qpwoeiru", package3.get_checksum().get_digest());
    EXPECT_EQ(97643154, package3.get_size());
    EXPECT_EQ("nevra3", package3.get_nevra());
    EXPECT_EQ("srpm3", package3.get_srpm());
}

}