#include "impl/manifest/operations/parser/parserfactory.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal::manifest;

using ::testing::ElementsAre;

TEST(ParserFactoryTest, ParseSimpleManifest) {
    auto file_path = std::string(getenv("PROJECT_SOURCE_DIR")) + "/test/data/manifest/simple.yaml";

    ParserFactory parser_factory;
    auto parser = parser_factory.create();
    auto manifest = parser->parse(file_path);

    EXPECT_EQ("rpm-package-manifest", manifest->get_document());
    EXPECT_EQ(1, manifest->get_version().get_major());
    EXPECT_EQ(2, manifest->get_version().get_minor());
    EXPECT_EQ(3, manifest->get_version().get_patch());

    auto & repositories = manifest->get_repositories().get();
    EXPECT_EQ(3, repositories.size());

    auto & repository1 = repositories.at("repo1");
    EXPECT_EQ("repo1", repository1->get_id());
    EXPECT_EQ("http://some.server.gov/folder/metalink", repository1->get_metalink());

    auto & repository2 = repositories.at("repo2");
    EXPECT_EQ("repo2", repository2->get_id());
    EXPECT_EQ("http://other.computer.lol/dir/for/pkgs/$arch/", repository2->get_baseurl());

    auto & repository3 = repositories.at("repo3");
    EXPECT_EQ("repo3", repository3->get_id());
    EXPECT_EQ("file:///home/user/my/repository", repository3->get_baseurl());
    EXPECT_EQ("https://my.user.repository.org/metalink", repository3->get_metalink());
    EXPECT_EQ("http://mirrors.user.repository.org/mirrors.txt", repository3->get_mirrorlist());

    EXPECT_EQ(2, manifest->get_packages().get().size());
    EXPECT_EQ(2, manifest->get_packages().get()["i686"].size());
    EXPECT_EQ(1, manifest->get_packages().get()["src"].size());

    auto & package1 = manifest->get_packages().get().at("i686")[0];
    EXPECT_EQ("repo1", package1->get_repo_id());
    EXPECT_EQ(152384, package1->get_size());
    EXPECT_EQ(ChecksumMethod::SHA512, package1->get_checksum().get_method());
    EXPECT_EQ("abcdef", package1->get_checksum().get_digest());
    EXPECT_EQ("", package1->get_module().get_name());
    EXPECT_EQ("", package1->get_module().get_stream());

    auto & package2 = manifest->get_packages().get().at("i686")[1];
    EXPECT_EQ("repo2", package2->get_repo_id());
    EXPECT_EQ("p/package2-3:4.5.6-2.r2.rpm", package2->get_location());
    EXPECT_EQ(378124894, package2->get_size());
    EXPECT_EQ(ChecksumMethod::MD5, package2->get_checksum().get_method());
    EXPECT_EQ("fedcba", package2->get_checksum().get_digest());
    EXPECT_EQ("name2", package2->get_module().get_name());
    EXPECT_EQ("stream2", package2->get_module().get_stream());

    auto & package3 = manifest->get_packages().get().at("src")[0];
    EXPECT_EQ("repo3", package3->get_repo_id());
    EXPECT_EQ("another/dir/file.here", package3->get_location());
    EXPECT_EQ(97643154, package3->get_size());
    EXPECT_EQ(ChecksumMethod::SHA256, package3->get_checksum().get_method());
    EXPECT_EQ("qpwoeiru", package3->get_checksum().get_digest());
    EXPECT_EQ("", package3->get_module().get_name());
    EXPECT_EQ("", package3->get_module().get_stream());
}

}