// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "libpkgmanifest/manifest/parser.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::manifest;

TEST(ApiManifestParserTest, ParseSimpleManifest) {
    auto file_path = std::string(std::getenv("PROJECT_SOURCE_DIR")) + "/test/data/manifest/simple.yaml";

    Parser parser;
    auto manifest = parser.parse(file_path);

    EXPECT_EQ("rpm-package-manifest", manifest.get_document());
    EXPECT_EQ(1, manifest.get_version().get_major());
    EXPECT_EQ(2, manifest.get_version().get_minor());
    EXPECT_EQ(3, manifest.get_version().get_patch());

    auto & repositories = manifest.get_repositories();
    EXPECT_EQ(3, repositories.size());

    auto repository1 = repositories.get("repo1");
    EXPECT_EQ("repo1", repository1.get_id());
    EXPECT_EQ("http://some.server.gov/folder/metalink", repository1.get_metalink());

    auto repository2 = repositories.get("repo2");
    EXPECT_EQ("repo2", repository2.get_id());
    EXPECT_EQ("http://other.computer.lol/dir/for/pkgs/$arch/", repository2.get_baseurl());

    auto repository3 = repositories.get("repo3");
    EXPECT_EQ("repo3", repository3.get_id());
    EXPECT_EQ("file:///home/user/my/repository", repository3.get_baseurl());
    EXPECT_EQ("https://my.user.repository.org/metalink", repository3.get_metalink());
    EXPECT_EQ("http://mirrors.user.repository.org/mirrors.txt", repository3.get_mirrorlist());

    auto & packages = manifest.get_packages();
    EXPECT_EQ(2, packages.get("i686").size());
    EXPECT_EQ(1, packages.get("src").size());

    auto i686_packages = packages.get("i686");
    auto & package1 = i686_packages[0];
    EXPECT_EQ("repo1", package1.get_repo_id());
    EXPECT_EQ("", package1.get_url());
    EXPECT_EQ(152384, package1.get_size());
    EXPECT_EQ("repo1", package1.get_repository().get_id());
    EXPECT_EQ("http://some.server.gov/folder/metalink", package1.get_repository().get_metalink());
    EXPECT_EQ(ChecksumMethod::SHA512, package1.get_checksum().get_method());
    EXPECT_EQ("abcdef", package1.get_checksum().get_digest());
    EXPECT_EQ("package1", package1.get_nevra().get_name());
    EXPECT_EQ("", package1.get_nevra().get_epoch());
    EXPECT_EQ("1.2.3", package1.get_nevra().get_version());
    EXPECT_EQ("1.r1", package1.get_nevra().get_release());
    EXPECT_EQ("i686", package1.get_nevra().get_arch());
    EXPECT_EQ("package1", package1.get_srpm().get_name());
    EXPECT_EQ("", package1.get_srpm().get_epoch());
    EXPECT_EQ("1.2.3", package1.get_srpm().get_version());
    EXPECT_EQ("1.r1", package1.get_srpm().get_release());
    EXPECT_EQ("src", package1.get_srpm().get_arch());
    EXPECT_EQ("", package1.get_module().get_name());
    EXPECT_EQ("", package1.get_module().get_stream());

    auto & package2 = i686_packages[1];
    EXPECT_EQ("repo2", package2.get_repo_id());
    EXPECT_EQ("p/package2-3:4.5.6-2.r2.rpm", package2.get_location());
    EXPECT_EQ("http://other.computer.lol/dir/for/pkgs/i686/p/package2-3:4.5.6-2.r2.rpm", package2.get_url());
    EXPECT_EQ(378124894, package2.get_size());
    EXPECT_EQ("repo2", package2.get_repository().get_id());
    EXPECT_EQ("http://other.computer.lol/dir/for/pkgs/$arch/", package2.get_repository().get_baseurl());
    EXPECT_EQ(ChecksumMethod::MD5, package2.get_checksum().get_method());
    EXPECT_EQ("fedcba", package2.get_checksum().get_digest());
    EXPECT_EQ("package2", package2.get_nevra().get_name());
    EXPECT_EQ("3", package2.get_nevra().get_epoch());
    EXPECT_EQ("4.5.6", package2.get_nevra().get_version());
    EXPECT_EQ("2.r2", package2.get_nevra().get_release());
    EXPECT_EQ("i686", package2.get_nevra().get_arch());
    EXPECT_EQ("", package2.get_srpm().to_string());
    EXPECT_EQ("name2", package2.get_module().get_name());
    EXPECT_EQ("stream2", package2.get_module().get_stream());

    auto src_packages = packages.get("src");
    auto & package3 = src_packages[0];
    EXPECT_EQ("repo3", package3.get_repo_id());
    EXPECT_EQ("another/dir/file.here", package3.get_location());
    EXPECT_EQ("file:///home/user/my/repository/another/dir/file.here", package3.get_url());
    EXPECT_EQ(97643154, package3.get_size());
    EXPECT_EQ("repo3", package3.get_repository().get_id());
    EXPECT_EQ("file:///home/user/my/repository", package3.get_repository().get_baseurl());
    EXPECT_EQ("https://my.user.repository.org/metalink", package3.get_repository().get_metalink());
    EXPECT_EQ("http://mirrors.user.repository.org/mirrors.txt", package3.get_repository().get_mirrorlist());
    EXPECT_EQ(ChecksumMethod::SHA256, package3.get_checksum().get_method());
    EXPECT_EQ("qpwoeiru", package3.get_checksum().get_digest());
    EXPECT_EQ("package3", package3.get_nevra().get_name());
    EXPECT_EQ("", package3.get_nevra().get_epoch());
    EXPECT_EQ("9.9", package3.get_nevra().get_version());
    EXPECT_EQ("1.r3", package3.get_nevra().get_release());
    EXPECT_EQ("src", package3.get_nevra().get_arch());
    EXPECT_EQ("", package3.get_srpm().to_string());
    EXPECT_EQ("", package3.get_module().get_name());
    EXPECT_EQ("", package3.get_module().get_stream());
}

}