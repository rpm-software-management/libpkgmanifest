#include "liblockfile/mocks/objects/checksum/checksummock.hpp"
#include "liblockfile/mocks/objects/lockfile/lockfilemock.hpp"
#include "liblockfile/mocks/objects/package/packagemock.hpp"
#include "liblockfile/mocks/objects/packages/packagesmock.hpp"
#include "liblockfile/mocks/objects/version/versionmock.hpp"

#include "liblockfile/wrappers/factory.hpp"

#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>

namespace {

using namespace liblockfile::internal;

using ::testing::NiceMock;
using ::testing::Ref;
using ::testing::Return;
using ::testing::ReturnPointee;
using ::testing::Test;

class SerializerFactoryTest : public Test {
protected:
    virtual void SetUp() {
        file_path = std::filesystem::temp_directory_path() / "SerializerFactoryTest.yaml";
    }

    virtual void TearDown() {
        std::error_code ec;
        std::filesystem::remove(file_path, ec);
    }

    std::filesystem::path file_path;
};

TEST_F(SerializerFactoryTest, SerializerSimpleLockFile) {
    const std::string simple_lockfile_yaml = R"(document: rpm-lockfile
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

    NiceMock<VersionMock> version;
    EXPECT_CALL(version, get_major()).WillOnce(Return(1));
    EXPECT_CALL(version, get_minor()).WillOnce(Return(2));
    EXPECT_CALL(version, get_patch()).WillOnce(Return(3));

    auto checksum1 = std::make_unique<NiceMock<ChecksumMock>>();
    auto checksum1_ptr = checksum1.get();
    EXPECT_CALL(*checksum1, get_method()).WillOnce(Return(liblockfile::ChecksumMethod::SHA512));
    EXPECT_CALL(*checksum1, get_digest()).WillOnce(Return("abcdef"));

    auto package1 = std::make_unique<NiceMock<PackageMock>>();
    EXPECT_CALL(*package1, get_repo_id()).WillOnce(Return("repo1"));
    EXPECT_CALL(*package1, get_url()).WillOnce(Return("url1"));
    EXPECT_CALL(*package1, get_checksum()).WillOnce(ReturnPointee(checksum1_ptr));
    EXPECT_CALL(*package1, get_size()).WillOnce(Return(152384));
    EXPECT_CALL(*package1, get_nevra()).WillOnce(Return("nevra1"));
    EXPECT_CALL(*package1, get_srpm()).WillOnce(Return("srpm1"));

    auto checksum2 = std::make_unique<NiceMock<ChecksumMock>>();
    auto checksum2_ptr = checksum2.get();
    EXPECT_CALL(*checksum2, get_method()).WillOnce(Return(liblockfile::ChecksumMethod::MD5));
    EXPECT_CALL(*checksum2, get_digest()).WillOnce(Return("fedcba"));

    auto package2 = std::make_unique<NiceMock<PackageMock>>();
    EXPECT_CALL(*package2, get_repo_id()).WillOnce(Return("repo2"));
    EXPECT_CALL(*package2, get_url()).WillOnce(Return("url2"));
    EXPECT_CALL(*package2, get_checksum()).WillOnce(ReturnPointee(checksum2_ptr));
    EXPECT_CALL(*package2, get_size()).WillOnce(Return(378124894));
    EXPECT_CALL(*package2, get_nevra()).WillOnce(Return("nevra2"));
    EXPECT_CALL(*package2, get_srpm()).WillOnce(Return("srpm2"));

    auto checksum3 = std::make_unique<NiceMock<ChecksumMock>>();
    auto checksum3_ptr = checksum3.get();
    EXPECT_CALL(*checksum3, get_method()).WillOnce(Return(liblockfile::ChecksumMethod::SHA256));
    EXPECT_CALL(*checksum3, get_digest()).WillOnce(Return("qpwoeiru"));

    auto package3 = std::make_unique<NiceMock<PackageMock>>();
    EXPECT_CALL(*package3, get_repo_id()).WillOnce(Return("repo3"));
    EXPECT_CALL(*package3, get_url()).WillOnce(Return("http://some.server.org/folder/nevra3.rpm"));
    EXPECT_CALL(*package3, get_checksum()).WillOnce(ReturnPointee(checksum3_ptr));
    EXPECT_CALL(*package3, get_size()).WillOnce(Return(97643154));
    EXPECT_CALL(*package3, get_nevra()).WillOnce(Return("nevra3"));
    EXPECT_CALL(*package3, get_srpm()).WillOnce(Return("srpm3"));

    std::vector<std::unique_ptr<IPackage>> i686_packages;
    i686_packages.push_back(std::move(package1));
    i686_packages.push_back(std::move(package2));

    std::vector<std::unique_ptr<IPackage>> src_packages;
    src_packages.push_back(std::move(package3));

    std::map<std::string, std::vector<std::unique_ptr<IPackage>>> package_map;
    package_map["i686"] = std::move(i686_packages);
    package_map["src"] = std::move(src_packages);

    NiceMock<PackagesMock> packages;
    EXPECT_CALL(packages, get()).WillOnce(ReturnPointee(&package_map));

    NiceMock<LockFileMock> file;
    EXPECT_CALL(file, get_document()).WillOnce(Return("rpm-lockfile"));
    EXPECT_CALL(file, get_version()).WillOnce(ReturnPointee(&version));
    EXPECT_CALL(file, get_packages()).WillOnce(ReturnPointee(&packages));

    auto serializer = Factory::create_serializer();
    serializer->serialize(file, file_path);

    std::ifstream output_file(file_path);
    std::stringstream read_file_buffer;
    read_file_buffer << output_file.rdbuf();

    EXPECT_EQ(read_file_buffer.str(), simple_lockfile_yaml);
}

}