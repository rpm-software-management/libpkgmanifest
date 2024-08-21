#include "libpkgmanifest/operations/parserfactory.hpp"

#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal;

TEST(ParserFactoryTest, ParseSimpleManifest) {
    auto file_path = std::string(getenv("PROJECT_SOURCE_DIR")) + "/test/data/simple.yaml";

    ParserFactory parser_factory;
    auto parser = parser_factory.create();
    auto manifest = parser->parse(file_path);

    EXPECT_EQ("rpm-manifest", manifest->get_document());
    EXPECT_EQ(1, manifest->get_version().get_major());
    EXPECT_EQ(2, manifest->get_version().get_minor());
    EXPECT_EQ(3, manifest->get_version().get_patch());

    EXPECT_EQ(2, manifest->get_packages().get().size());
    EXPECT_EQ(2, manifest->get_packages().get()["i686"].size());
    EXPECT_EQ(1, manifest->get_packages().get()["src"].size());

    auto & package1 = manifest->get_packages().get().at("i686")[0];
    EXPECT_EQ("i686", package1->get_arch());
    EXPECT_EQ("repo1", package1->get_repo_id());
    EXPECT_EQ("url1", package1->get_url());
    EXPECT_EQ(libpkgmanifest::ChecksumMethod::SHA512, package1->get_checksum().get_method());
    EXPECT_EQ("abcdef", package1->get_checksum().get_digest());
    EXPECT_EQ(152384, package1->get_size());
    EXPECT_EQ("nevra1", package1->get_nevra());
    EXPECT_EQ("srpm1", package1->get_srpm());

    auto & package2 = manifest->get_packages().get().at("i686")[1];
    EXPECT_EQ("i686", package2->get_arch());
    EXPECT_EQ("repo2", package2->get_repo_id());
    EXPECT_EQ("url2", package2->get_url());
    EXPECT_EQ(libpkgmanifest::ChecksumMethod::MD5, package2->get_checksum().get_method());
    EXPECT_EQ("fedcba", package2->get_checksum().get_digest());
    EXPECT_EQ(378124894, package2->get_size());
    EXPECT_EQ("nevra2", package2->get_nevra());
    EXPECT_EQ("srpm2", package2->get_srpm());

    auto & package3 = manifest->get_packages().get().at("src")[0];
    EXPECT_EQ("src", package3->get_arch());
    EXPECT_EQ("repo3", package3->get_repo_id());
    EXPECT_EQ("http://some.server.org/folder/nevra3.rpm", package3->get_url());
    EXPECT_EQ(libpkgmanifest::ChecksumMethod::SHA256, package3->get_checksum().get_method());
    EXPECT_EQ("qpwoeiru", package3->get_checksum().get_digest());
    EXPECT_EQ(97643154, package3->get_size());
    EXPECT_EQ("nevra3", package3->get_nevra());
    EXPECT_EQ("srpm3", package3->get_srpm());
}

}