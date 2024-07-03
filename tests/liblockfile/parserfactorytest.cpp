#include "liblockfile/parserfactory.hpp"

#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>

namespace {

using namespace liblockfile;

using ::testing::Test;

class ParserFactoryTest : public Test {
protected:
    virtual void SetUp() {
        file_path = std::filesystem::temp_directory_path() / "ParserFactoryTest.yaml";
    }

    virtual void TearDown() {
        std::error_code ec;
        std::filesystem::remove(file_path, ec);
    }

    std::filesystem::path file_path;
};

TEST_F(ParserFactoryTest, ParseSimpleLockFile) {
    const std::string simple_lockfile_yaml = R"(
        document: rpm-lockfile
        version: 1.2.3
        data:
            packages:
                i686:
                    - repoid: repo1
                      url: url1
                      checksum: sha512:abcdef
                      size: 152384
                      nevra: nevra1
                      srpm: srpm1
                    - repoid: repo2
                      url: url2
                      checksum: md5:fedcba
                      size: 378124894
                      nevra: nevra2
                      srpm: srpm2
                src:
                    - repoid: repo3
                      url: http://some.server.org/folder/nevra3.rpm
                      checksum: SHA256:qpwoeiru
                      size: 97643154
                      nevra: nevra3
                      srpm: srpm3
    )";

    std::ofstream yaml_file(file_path);
    yaml_file << simple_lockfile_yaml << std::flush;

    auto parser = ParserFactory::create();
    auto lock_file = parser->parse(file_path);

    EXPECT_EQ("rpm-lockfile", lock_file->get_document());
    EXPECT_EQ(1, lock_file->get_version().get_major());
    EXPECT_EQ(2, lock_file->get_version().get_minor());
    EXPECT_EQ(3, lock_file->get_version().get_patch());

    EXPECT_EQ(2, lock_file->get_packages().get().size());
    EXPECT_EQ(2, lock_file->get_packages().get("i686").size());
    EXPECT_EQ(1, lock_file->get_packages().get("src").size());

    auto & package1 = lock_file->get_packages().get().at("i686")[0];
    EXPECT_EQ("i686", package1->get_arch());
    EXPECT_EQ("repo1", package1->get_repo_id());
    EXPECT_EQ("url1", package1->get_url());
    EXPECT_EQ(ChecksumMethod::SHA512, package1->get_checksum().get_method());
    EXPECT_EQ("abcdef", package1->get_checksum().get_digest());
    EXPECT_EQ(152384, package1->get_size());
    EXPECT_EQ("nevra1", package1->get_nevra());
    EXPECT_EQ("srpm1", package1->get_srpm());

    auto & package2 = lock_file->get_packages().get().at("i686")[1];
    EXPECT_EQ("i686", package2->get_arch());
    EXPECT_EQ("repo2", package2->get_repo_id());
    EXPECT_EQ("url2", package2->get_url());
    EXPECT_EQ(ChecksumMethod::MD5, package2->get_checksum().get_method());
    EXPECT_EQ("fedcba", package2->get_checksum().get_digest());
    EXPECT_EQ(378124894, package2->get_size());
    EXPECT_EQ("nevra2", package2->get_nevra());
    EXPECT_EQ("srpm2", package2->get_srpm());

    auto & package3 = lock_file->get_packages().get().at("src")[0];
    EXPECT_EQ("src", package3->get_arch());
    EXPECT_EQ("repo3", package3->get_repo_id());
    EXPECT_EQ("http://some.server.org/folder/nevra3.rpm", package3->get_url());
    EXPECT_EQ(ChecksumMethod::SHA256, package3->get_checksum().get_method());
    EXPECT_EQ("qpwoeiru", package3->get_checksum().get_digest());
    EXPECT_EQ(97643154, package3->get_size());
    EXPECT_EQ("nevra3", package3->get_nevra());
    EXPECT_EQ("srpm3", package3->get_srpm());
}

}