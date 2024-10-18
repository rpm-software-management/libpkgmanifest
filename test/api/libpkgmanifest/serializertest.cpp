#include "libpkgmanifest/operations/serializer.hpp"

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
  repositories:
    - id: repo1
      metalink: http://some.server.gov/folder/metalink
    - id: repo2
      baseurl: http://other.computer.lol/dir/for/pkgs/$arch/
    - id: repo3
      baseurl: file:///home/user/my/repository
      metalink: https://my.user.repository.org/metalink
      mirrorlist: http://mirrors.user.repository.org/mirrors.txt
  packages:
    i686:
      - name: package1
        repo_id: repo1
        checksum: sha512:abcdef
        size: 152384
        evr: 1.2.3-1.r1
        srpm: package1-1.2.3-1.r1.src
      - name: package2
        repo_id: repo2
        location: p/package2-3:4.5.6-2.r2.rpm
        checksum: md5:fedcba
        size: 378124894
        evr: 3:4.5.6-2.r2
        module: name2:stream2
    src:
      - name: package3
        repo_id: repo3
        location: another/dir/file.here
        checksum: sha256:qpwoeiru
        size: 97643154
        evr: 9.9-1.r3)";

    Repository repository1;
    repository1.set_id("repo1");
    repository1.set_metalink("http://some.server.gov/folder/metalink");

    Repository repository2;
    repository2.set_id("repo2");
    repository2.set_baseurl("http://other.computer.lol/dir/for/pkgs/$arch/");

    Repository repository3;
    repository3.set_id("repo3");
    repository3.set_baseurl("file:///home/user/my/repository");
    repository3.set_metalink("https://my.user.repository.org/metalink");
    repository3.set_mirrorlist("http://mirrors.user.repository.org/mirrors.txt");

    Package package1;
    package1.set_repo_id("repo1");
    package1.set_size(152384);
    package1.get_checksum().set_method(libpkgmanifest::ChecksumMethod::SHA512);
    package1.get_checksum().set_digest("abcdef");
    package1.get_nevra().set_name("package1");
    package1.get_nevra().set_version("1.2.3");
    package1.get_nevra().set_release("1.r1");
    package1.get_nevra().set_arch("i686");
    package1.get_srpm().set_name("package1");
    package1.get_srpm().set_version("1.2.3");
    package1.get_srpm().set_release("1.r1");
    package1.get_srpm().set_arch("src");

    Package package2;
    package2.set_repo_id("repo2");
    package2.set_location("p/package2-3:4.5.6-2.r2.rpm");
    package2.set_size(378124894);
    package2.get_checksum().set_method(libpkgmanifest::ChecksumMethod::MD5);
    package2.get_checksum().set_digest("fedcba");
    package2.get_nevra().set_name("package2");
    package2.get_nevra().set_epoch("3");
    package2.get_nevra().set_version("4.5.6");
    package2.get_nevra().set_release("2.r2");
    package2.get_nevra().set_arch("i686");
    package2.get_module().set_name("name2");
    package2.get_module().set_stream("stream2");

    Package package3;
    package3.set_repo_id("repo3");
    package3.set_location("another/dir/file.here");
    package3.set_size(97643154);
    package3.get_checksum().set_method(libpkgmanifest::ChecksumMethod::SHA256);
    package3.get_checksum().set_digest("qpwoeiru");
    package3.get_nevra().set_name("package3");
    package3.get_nevra().set_version("9.9");
    package3.get_nevra().set_release("1.r3");
    package3.get_nevra().set_arch("src");

    Manifest manifest;
    manifest.set_document("my-manifest");
    manifest.get_version().set_major(1);
    manifest.get_version().set_minor(2);
    manifest.get_version().set_patch(3);
    manifest.get_repositories().add(repository1);
    manifest.get_repositories().add(repository2);
    manifest.get_repositories().add(repository3);
    manifest.get_packages().add(package1);
    manifest.get_packages().add(package2);
    manifest.get_packages().add(package3);

    Serializer serializer;
    serializer.serialize_manifest(manifest, file_path);

    std::ifstream output_file(file_path);
    std::stringstream read_file_buffer;
    read_file_buffer << output_file.rdbuf();

    EXPECT_EQ(read_file_buffer.str(), simple_manifest_yaml);
}

TEST_F(ApiSerializerTest, SerializeEmptyManifest) {
    const std::string empty_manifest_yaml = R"(document: rpm-package-manifest
version: 0.2.0
data:
  repositories: ~
  packages: ~)";

    Manifest manifest;
    Serializer serializer;
    serializer.serialize_manifest(manifest, file_path);

    std::ifstream output_file(file_path);
    std::stringstream read_file_buffer;
    read_file_buffer << output_file.rdbuf();

    EXPECT_EQ(read_file_buffer.str(), empty_manifest_yaml);
}

}