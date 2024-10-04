#include "libpkgmanifest/parser.hpp"

#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest;

TEST(ApiParserTest, ParseSimpleManifest) {
    auto file_path = std::string(std::getenv("PROJECT_SOURCE_DIR")) + "/test/data/simple.yaml";

    Parser parser;
    auto manifest = parser.parse(file_path);

    EXPECT_EQ("rpm-package-manifest", manifest.get_document());
    EXPECT_EQ(1, manifest.get_version().get_major());
    EXPECT_EQ(2, manifest.get_version().get_minor());
    EXPECT_EQ(3, manifest.get_version().get_patch());

    auto repositories = manifest.get_repositories().get();
    EXPECT_EQ(3, repositories.size());

    auto & repository1 = repositories.at("repo1");
    EXPECT_EQ("repo1", repository1.get_id());
    EXPECT_EQ("http://some.server.gov/folder", repository1.get_url());

    auto & repository2 = repositories.at("repo2");
    EXPECT_EQ("repo2", repository2.get_id());
    EXPECT_EQ("http://other.computer.lol/dir/for/pkgs/$arch/", repository2.get_url());

    auto & repository3 = repositories.at("repo3");
    EXPECT_EQ("repo3", repository3.get_id());
    EXPECT_EQ("file:///home/user/my/repository", repository3.get_url());

    auto packages = manifest.get_packages().get();
    EXPECT_EQ(2, packages.size());
    EXPECT_EQ(2, packages["i686"].size());
    EXPECT_EQ(1, packages["src"].size());

    auto i686_packages = manifest.get_packages().get("i686");
    EXPECT_EQ(2, i686_packages.size());

    auto src_packages = manifest.get_packages().get("src");
    EXPECT_EQ(1, src_packages.size());

    auto & package1 = packages.at("i686")[0];
    EXPECT_EQ("repo1", package1.get_repo_id());
    EXPECT_EQ("pkgs/package1.rpm", package1.get_location());
    EXPECT_EQ("http://some.server.gov/folder/pkgs/package1.rpm", package1.get_url());
    EXPECT_EQ(152384, package1.get_size());
    EXPECT_EQ("repo1", package1.get_repository().get_id());
    EXPECT_EQ("http://some.server.gov/folder", package1.get_repository().get_url());
    EXPECT_EQ(libpkgmanifest::ChecksumMethod::SHA512, package1.get_checksum().get_method());
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

    auto & package2 = packages.at("i686")[1];
    EXPECT_EQ("repo2", package2.get_repo_id());
    EXPECT_EQ("p/package2-3:4.5.6-2.r2.rpm", package2.get_location());
    EXPECT_EQ("http://other.computer.lol/dir/for/pkgs/i686/p/package2-3:4.5.6-2.r2.rpm", package2.get_url());
    EXPECT_EQ(378124894, package2.get_size());
    EXPECT_EQ("repo2", package2.get_repository().get_id());
    EXPECT_EQ("http://other.computer.lol/dir/for/pkgs/$arch/", package2.get_repository().get_url());
    EXPECT_EQ(libpkgmanifest::ChecksumMethod::MD5, package2.get_checksum().get_method());
    EXPECT_EQ("fedcba", package2.get_checksum().get_digest());
    EXPECT_EQ("package2", package2.get_nevra().get_name());
    EXPECT_EQ("3", package2.get_nevra().get_epoch());
    EXPECT_EQ("4.5.6", package2.get_nevra().get_version());
    EXPECT_EQ("2.r2", package2.get_nevra().get_release());
    EXPECT_EQ("i686", package2.get_nevra().get_arch());
    EXPECT_EQ("", package2.get_srpm().to_string());
    EXPECT_EQ("name2", package2.get_module().get_name());
    EXPECT_EQ("stream2", package2.get_module().get_stream());

    auto & package3 = packages.at("src")[0];
    EXPECT_EQ("repo3", package3.get_repo_id());
    EXPECT_EQ("another/dir/file.here", package3.get_location());
    EXPECT_EQ("file:///home/user/my/repository/another/dir/file.here", package3.get_url());
    EXPECT_EQ(97643154, package3.get_size());
    EXPECT_EQ("repo3", package3.get_repository().get_id());
    EXPECT_EQ("file:///home/user/my/repository", package3.get_repository().get_url());
    EXPECT_EQ(libpkgmanifest::ChecksumMethod::SHA256, package3.get_checksum().get_method());
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