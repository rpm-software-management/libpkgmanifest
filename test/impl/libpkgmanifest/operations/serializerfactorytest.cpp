#include "libpkgmanifest/mocks/objects/checksum/checksummock.hpp"
#include "libpkgmanifest/mocks/objects/manifest/manifestmock.hpp"
#include "libpkgmanifest/mocks/objects/module/modulemock.hpp"
#include "libpkgmanifest/mocks/objects/nevra/nevramock.hpp"
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
      - name: package1
        repoid: repo1
        checksum: sha512:abcdef
        size: 152384
        evr: 1.2.3-1.r1
        srpm: package1-1.2.3-1.r1.src
      - name: package2
        url: http://some.server.org/folder/nevra2.rpm
        checksum: md5:fedcba
        size: 378124894
        evr: 3:4.5.6-2.r2
        module: name2:stream2
    src:
      - name: package3
        repoid: repo3
        checksum: sha256:qpwoeiru
        size: 97643154
        evr: 9.9-1.r3)";

    NiceMock<VersionMock> version;
    EXPECT_CALL(version, get_major()).WillOnce(Return(1));
    EXPECT_CALL(version, get_minor()).WillOnce(Return(2));
    EXPECT_CALL(version, get_patch()).WillOnce(Return(3));

    auto checksum1 = std::make_unique<NiceMock<ChecksumMock>>();
    EXPECT_CALL(*checksum1, get_method()).WillOnce(Return(libpkgmanifest::ChecksumMethod::SHA512));
    EXPECT_CALL(*checksum1, get_digest()).WillOnce(Return("abcdef"));

    auto nevra1 = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*nevra1, get_name()).WillOnce(Return("package1"));
    EXPECT_CALL(*nevra1, to_evr_string()).WillOnce(Return("1.2.3-1.r1"));

    auto srpm1 = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*srpm1, get_name()).WillOnce(Return("package1"));
    EXPECT_CALL(*srpm1, to_string()).WillOnce(Return("package1-1.2.3-1.r1.src"));

    auto module1 = std::make_unique<NiceMock<ModuleMock>>();
    EXPECT_CALL(*module1, get_name()).WillRepeatedly(Return(""));

    auto package1 = std::make_unique<NiceMock<PackageMock>>();
    EXPECT_CALL(*package1, get_repo_id()).WillOnce(Return("repo1"));
    EXPECT_CALL(*package1, get_url()).WillOnce(Return(""));
    EXPECT_CALL(*package1, get_size()).WillOnce(Return(152384));
    EXPECT_CALL(Const(*package1), get_checksum()).WillOnce(ReturnPointee(checksum1.get()));
    EXPECT_CALL(Const(*package1), get_nevra()).WillOnce(ReturnPointee(nevra1.get()));
    EXPECT_CALL(Const(*package1), get_srpm()).WillOnce(ReturnPointee(srpm1.get()));
    EXPECT_CALL(Const(*package1), get_module()).WillOnce(ReturnPointee(module1.get()));

    auto checksum2 = std::make_unique<NiceMock<ChecksumMock>>();
    EXPECT_CALL(*checksum2, get_method()).WillOnce(Return(libpkgmanifest::ChecksumMethod::MD5));
    EXPECT_CALL(*checksum2, get_digest()).WillOnce(Return("fedcba"));

    auto nevra2 = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*nevra2, get_name()).WillOnce(Return("package2"));
    EXPECT_CALL(*nevra2, to_evr_string()).WillOnce(Return("3:4.5.6-2.r2"));

    auto srpm2 = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*srpm2, get_name()).WillOnce(Return(""));

    auto module2 = std::make_unique<NiceMock<ModuleMock>>();
    EXPECT_CALL(*module2, get_name()).WillRepeatedly(Return("name2"));
    EXPECT_CALL(*module2, get_stream()).WillOnce(Return("stream2"));

    auto package2 = std::make_unique<NiceMock<PackageMock>>();
    EXPECT_CALL(*package2, get_repo_id()).WillOnce(Return(""));
    EXPECT_CALL(*package2, get_url()).WillOnce(Return("http://some.server.org/folder/nevra2.rpm"));
    EXPECT_CALL(*package2, get_size()).WillOnce(Return(378124894));
    EXPECT_CALL(Const(*package2), get_checksum()).WillOnce(ReturnPointee(checksum2.get()));
    EXPECT_CALL(Const(*package2), get_nevra()).WillOnce(ReturnPointee(nevra2.get()));
    EXPECT_CALL(Const(*package2), get_srpm()).WillOnce(ReturnPointee(srpm2.get()));
    EXPECT_CALL(Const(*package2), get_module()).WillOnce(ReturnPointee(module2.get()));

    auto checksum3 = std::make_unique<NiceMock<ChecksumMock>>();
    EXPECT_CALL(*checksum3, get_method()).WillOnce(Return(libpkgmanifest::ChecksumMethod::SHA256));
    EXPECT_CALL(*checksum3, get_digest()).WillOnce(Return("qpwoeiru"));

    auto nevra3 = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*nevra3, get_name()).WillRepeatedly(Return("package3"));
    EXPECT_CALL(*nevra3, to_evr_string()).WillOnce(Return("9.9-1.r3"));

    auto srpm3 = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*srpm3, get_name()).WillOnce(Return(""));

    auto module3 = std::make_unique<NiceMock<ModuleMock>>();
    EXPECT_CALL(*module3, get_name()).WillRepeatedly(Return(""));

    auto package3 = std::make_unique<NiceMock<PackageMock>>();
    EXPECT_CALL(*package3, get_repo_id()).WillOnce(Return("repo3"));
    EXPECT_CALL(*package3, get_url()).WillOnce(Return(""));
    EXPECT_CALL(*package3, get_size()).WillOnce(Return(97643154));
    EXPECT_CALL(Const(*package3), get_checksum()).WillOnce(ReturnPointee(checksum3.get()));
    EXPECT_CALL(Const(*package3), get_nevra()).WillOnce(ReturnPointee(nevra3.get()));
    EXPECT_CALL(Const(*package3), get_srpm()).WillOnce(ReturnPointee(srpm3.get()));
    EXPECT_CALL(Const(*package3), get_module()).WillOnce(ReturnPointee(module3.get()));

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