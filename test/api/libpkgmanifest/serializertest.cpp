#include "libpkgmanifest/serializer.hpp"

#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>

namespace {

using namespace libpkgmanifest;

using ::testing::Test;

class ApiSerializerTest : public Test {
protected:
    virtual void SetUp() {
        file_path = std::filesystem::temp_directory_path() / "ApiSerializerTest.yaml";
    }

    virtual void TearDown() {
        std::error_code ec;
        std::filesystem::remove(file_path, ec);
    }

    std::filesystem::path file_path;
};

TEST_F(ApiSerializerTest, SerializeSimpleManifest) {
    const std::string simple_manifest_yaml = R"(document: my-manifest
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
        checksum: sha256:qpwoeiru
        size: 97643154
        nevra: nevra3
        srpm: srpm3)";

    Package package1;
    package1.set_arch("i686");
    package1.set_repo_id("repo1");
    package1.set_url("url1");
    package1.get_checksum().set_method(libpkgmanifest::ChecksumMethod::SHA512);
    package1.get_checksum().set_digest("abcdef");
    package1.set_size(152384);
    package1.set_nevra("nevra1");
    package1.set_srpm("srpm1");

    Package package2;
    package2.set_arch("i686");
    package2.set_repo_id("repo2");
    package2.set_url("url2");
    package2.get_checksum().set_method(libpkgmanifest::ChecksumMethod::MD5);
    package2.get_checksum().set_digest("fedcba");
    package2.set_size(378124894);
    package2.set_nevra("nevra2");
    package2.set_srpm("srpm2");

    Package package3;
    package3.set_arch("src");
    package3.set_repo_id("repo3");
    package3.set_url("http://some.server.org/folder/nevra3.rpm");
    package3.get_checksum().set_method(libpkgmanifest::ChecksumMethod::SHA256);
    package3.get_checksum().set_digest("qpwoeiru");
    package3.set_size(97643154);
    package3.set_nevra("nevra3");
    package3.set_srpm("srpm3");

    Manifest manifest;
    manifest.set_document("my-manifest");
    manifest.get_version().set_major(1);
    manifest.get_version().set_minor(2);
    manifest.get_version().set_patch(3);
    manifest.get_packages().add(package1);
    manifest.get_packages().add(package2);
    manifest.get_packages().add(package3);

    Serializer serializer;
    serializer.serialize(manifest, file_path);

    std::ifstream output_file(file_path);
    std::stringstream read_file_buffer;
    read_file_buffer << output_file.rdbuf();

    EXPECT_EQ(read_file_buffer.str(), simple_manifest_yaml);
}

TEST_F(ApiSerializerTest, SerializeEmptyManifest) {
    const std::string empty_manifest_yaml = R"(document: rpm-package-manifest
version: 0.0.1
data:
  packages: ~)";

    Manifest manifest;
    Serializer serializer;
    serializer.serialize(manifest, file_path);

    std::ifstream output_file(file_path);
    std::stringstream read_file_buffer;
    read_file_buffer << output_file.rdbuf();

    EXPECT_EQ(read_file_buffer.str(), empty_manifest_yaml);
}

}