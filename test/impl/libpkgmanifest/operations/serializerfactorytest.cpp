#include "libpkgmanifest/mocks/objects/checksum/checksummock.hpp"
#include "libpkgmanifest/mocks/objects/module/modulemock.hpp"
#include "libpkgmanifest/mocks/objects/manifest/manifestmock.hpp"
#include "libpkgmanifest/mocks/objects/package/packagemock.hpp"
#include "libpkgmanifest/mocks/objects/packages/packagesmock.hpp"
#include "libpkgmanifest/mocks/objects/version/versionmock.hpp"

#include "libpkgmanifest/operations/serializerfactory.hpp"

#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>

namespace {

using namespace libpkgmanifest::internal;

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

TEST_F(SerializerFactoryTest, SerializeSimpleManifest) {
    const std::string simple_manifest_yaml = R"(document: my-manifest
version: 1.2.3
data:
  packages:
    i686:
      - repoid: repo1
        checksum: sha512:abcdef
        size: 152384
        nevra: nevra1
        srpm: srpm1
      - url: http://some.server.org/folder/nevra2.rpm
        checksum: md5:fedcba
        size: 378124894
        nevra: nevra2
        module: name2:stream2
    src:
      - repoid: repo3
        checksum: sha256:qpwoeiru
        size: 97643154
        nevra: nevra3)";

    NiceMock<VersionMock> version;
    EXPECT_CALL(version, get_major()).WillOnce(Return(1));
    EXPECT_CALL(version, get_minor()).WillOnce(Return(2));
    EXPECT_CALL(version, get_patch()).WillOnce(Return(3));

    auto checksum1 = std::make_unique<NiceMock<ChecksumMock>>();
    auto checksum1_ptr = checksum1.get();
    EXPECT_CALL(*checksum1, get_method()).WillOnce(Return(libpkgmanifest::ChecksumMethod::SHA512));
    EXPECT_CALL(*checksum1, get_digest()).WillOnce(Return("abcdef"));

    auto module1 = std::make_unique<NiceMock<ModuleMock>>();
    auto module1_ptr = module1.get();
    EXPECT_CALL(*module1, get_name()).WillRepeatedly(Return("")); // TODO

    auto package1 = std::make_unique<NiceMock<PackageMock>>();
    EXPECT_CALL(*package1, get_repo_id()).WillOnce(Return("repo1"));
    EXPECT_CALL(*package1, get_url()).WillOnce(Return(""));
    EXPECT_CALL(Const(*package1), get_checksum()).WillOnce(ReturnPointee(checksum1_ptr));
    EXPECT_CALL(*package1, get_size()).WillOnce(Return(152384));
    EXPECT_CALL(*package1, get_nevra()).WillOnce(Return("nevra1"));
    EXPECT_CALL(*package1, get_srpm()).WillOnce(Return("srpm1"));
    EXPECT_CALL(Const(*package1), get_module()).WillOnce(ReturnPointee(module1_ptr));

    auto checksum2 = std::make_unique<NiceMock<ChecksumMock>>();
    auto checksum2_ptr = checksum2.get();
    EXPECT_CALL(*checksum2, get_method()).WillOnce(Return(libpkgmanifest::ChecksumMethod::MD5));
    EXPECT_CALL(*checksum2, get_digest()).WillOnce(Return("fedcba"));

    auto module2 = std::make_unique<NiceMock<ModuleMock>>();
    auto module2_ptr = module2.get();
    EXPECT_CALL(*module2, get_name()).WillRepeatedly(Return("name2"));
    EXPECT_CALL(*module2, get_stream()).WillOnce(Return("stream2"));

    auto package2 = std::make_unique<NiceMock<PackageMock>>();
    EXPECT_CALL(*package2, get_repo_id()).WillOnce(Return(""));
    EXPECT_CALL(*package2, get_url()).WillOnce(Return("http://some.server.org/folder/nevra2.rpm"));
    EXPECT_CALL(Const(*package2), get_checksum()).WillOnce(ReturnPointee(checksum2_ptr));
    EXPECT_CALL(*package2, get_size()).WillOnce(Return(378124894));
    EXPECT_CALL(*package2, get_nevra()).WillOnce(Return("nevra2"));
    EXPECT_CALL(*package2, get_srpm()).WillOnce(Return(""));
    EXPECT_CALL(Const(*package2), get_module()).WillOnce(ReturnPointee(module2_ptr));

    auto checksum3 = std::make_unique<NiceMock<ChecksumMock>>();
    auto checksum3_ptr = checksum3.get();
    EXPECT_CALL(*checksum3, get_method()).WillOnce(Return(libpkgmanifest::ChecksumMethod::SHA256));
    EXPECT_CALL(*checksum3, get_digest()).WillOnce(Return("qpwoeiru"));

    auto module3 = std::make_unique<NiceMock<ModuleMock>>();
    auto module3_ptr = module3.get();
    EXPECT_CALL(*module3, get_name()).WillRepeatedly(Return(""));

    auto package3 = std::make_unique<NiceMock<PackageMock>>();
    EXPECT_CALL(*package3, get_repo_id()).WillOnce(Return("repo3"));
    EXPECT_CALL(*package3, get_url()).WillOnce(Return(""));
    EXPECT_CALL(Const(*package3), get_checksum()).WillOnce(ReturnPointee(checksum3_ptr));
    EXPECT_CALL(*package3, get_size()).WillOnce(Return(97643154));
    EXPECT_CALL(*package3, get_nevra()).WillOnce(Return("nevra3"));
    EXPECT_CALL(*package3, get_srpm()).WillOnce(Return(""));
    EXPECT_CALL(Const(*package3), get_module()).WillOnce(ReturnPointee(module3_ptr));

    std::vector<std::unique_ptr<IPackage>> i686_packages;
    i686_packages.push_back(std::move(package1));
    i686_packages.push_back(std::move(package2));

    std::vector<std::unique_ptr<IPackage>> src_packages;
    src_packages.push_back(std::move(package3));

    std::map<std::string, std::vector<std::unique_ptr<IPackage>>> package_map;
    package_map["i686"] = std::move(i686_packages);
    package_map["src"] = std::move(src_packages);

    NiceMock<PackagesMock> packages;
    EXPECT_CALL(Const(packages), get()).WillOnce(ReturnPointee(&package_map));

    NiceMock<ManifestMock> manifest;
    EXPECT_CALL(manifest, get_document()).WillOnce(Return("my-manifest"));
    EXPECT_CALL(Const(manifest), get_version()).WillOnce(ReturnPointee(&version));
    EXPECT_CALL(Const(manifest), get_packages()).WillOnce(ReturnPointee(&packages));

    SerializerFactory serializer_factory;
    auto serializer = serializer_factory.create();
    serializer->serialize(manifest, file_path);

    std::ifstream output_file(file_path);
    std::stringstream read_file_buffer;
    read_file_buffer << output_file.rdbuf();

    EXPECT_EQ(read_file_buffer.str(), simple_manifest_yaml);
}

}