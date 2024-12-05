#include "impl/manifest/mocks/objects/checksum/checksummock.hpp"
#include "impl/manifest/mocks/objects/manifest/manifestmock.hpp"
#include "impl/manifest/mocks/objects/module/modulemock.hpp"
#include "impl/manifest/mocks/objects/nevra/nevramock.hpp"
#include "impl/manifest/mocks/objects/package/packagemock.hpp"
#include "impl/manifest/mocks/objects/packages/packagesmock.hpp"
#include "impl/common/mocks/objects/repository/repositorymock.hpp"
#include "impl/common/mocks/objects/repositories/repositoriesmock.hpp"
#include "impl/common/mocks/objects/version/versionmock.hpp"

#include "impl/manifest/operations/serializer/serializerfactory.hpp"

#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>

namespace {

using namespace libpkgmanifest::internal::manifest;

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

    auto repository1 = std::make_unique<NiceMock<RepositoryMock>>();
    EXPECT_CALL(*repository1, get_id()).WillRepeatedly(Return("repo1"));
    EXPECT_CALL(*repository1, get_metalink()).WillOnce(Return("http://some.server.gov/folder/metalink"));

    auto repository2 = std::make_unique<NiceMock<RepositoryMock>>();
    EXPECT_CALL(*repository2, get_id()).WillRepeatedly(Return("repo2"));
    EXPECT_CALL(*repository2, get_baseurl()).WillOnce(Return("http://other.computer.lol/dir/for/pkgs/$arch/"));

    auto repository3 = std::make_unique<NiceMock<RepositoryMock>>();
    EXPECT_CALL(*repository3, get_id()).WillRepeatedly(Return("repo3"));
    EXPECT_CALL(*repository3, get_baseurl()).WillOnce(Return("file:///home/user/my/repository"));
    EXPECT_CALL(*repository3, get_metalink()).WillOnce(Return("https://my.user.repository.org/metalink"));
    EXPECT_CALL(*repository3, get_mirrorlist()).WillOnce(Return("http://mirrors.user.repository.org/mirrors.txt"));

    std::map<std::string, std::unique_ptr<IRepository>> repository_map;
    repository_map["repo1"] = std::move(repository1);
    repository_map["repo2"] = std::move(repository2);
    repository_map["repo3"] = std::move(repository3);

    NiceMock<RepositoriesMock> repositories;
    EXPECT_CALL(Const(repositories), get()).WillRepeatedly(ReturnPointee(&repository_map));

    NiceMock<VersionMock> version;
    EXPECT_CALL(version, get_major()).WillOnce(Return(1));
    EXPECT_CALL(version, get_minor()).WillOnce(Return(2));
    EXPECT_CALL(version, get_patch()).WillOnce(Return(3));

    auto checksum1 = std::make_unique<NiceMock<ChecksumMock>>();
    EXPECT_CALL(*checksum1, get_method()).WillOnce(Return(ChecksumMethod::SHA512));
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
    EXPECT_CALL(*package1, get_repo_id()).WillRepeatedly(Return("repo1"));
    EXPECT_CALL(*package1, get_size()).WillOnce(Return(152384));
    EXPECT_CALL(Const(*package1), get_checksum()).WillOnce(ReturnPointee(checksum1.get()));
    EXPECT_CALL(Const(*package1), get_nevra()).WillOnce(ReturnPointee(nevra1.get()));
    EXPECT_CALL(Const(*package1), get_srpm()).WillOnce(ReturnPointee(srpm1.get()));
    EXPECT_CALL(Const(*package1), get_module()).WillOnce(ReturnPointee(module1.get()));

    auto checksum2 = std::make_unique<NiceMock<ChecksumMock>>();
    EXPECT_CALL(*checksum2, get_method()).WillOnce(Return(ChecksumMethod::MD5));
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
    EXPECT_CALL(*package2, get_repo_id()).WillRepeatedly(Return("repo2"));
    EXPECT_CALL(*package2, get_location()).WillOnce(Return("p/package2-3:4.5.6-2.r2.rpm"));
    EXPECT_CALL(*package2, get_size()).WillOnce(Return(378124894));
    EXPECT_CALL(Const(*package2), get_checksum()).WillOnce(ReturnPointee(checksum2.get()));
    EXPECT_CALL(Const(*package2), get_nevra()).WillOnce(ReturnPointee(nevra2.get()));
    EXPECT_CALL(Const(*package2), get_srpm()).WillOnce(ReturnPointee(srpm2.get()));
    EXPECT_CALL(Const(*package2), get_module()).WillOnce(ReturnPointee(module2.get()));

    auto checksum3 = std::make_unique<NiceMock<ChecksumMock>>();
    EXPECT_CALL(*checksum3, get_method()).WillOnce(Return(ChecksumMethod::SHA256));
    EXPECT_CALL(*checksum3, get_digest()).WillOnce(Return("qpwoeiru"));

    auto nevra3 = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*nevra3, get_name()).WillRepeatedly(Return("package3"));
    EXPECT_CALL(*nevra3, to_evr_string()).WillOnce(Return("9.9-1.r3"));

    auto srpm3 = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*srpm3, get_name()).WillOnce(Return(""));

    auto module3 = std::make_unique<NiceMock<ModuleMock>>();
    EXPECT_CALL(*module3, get_name()).WillRepeatedly(Return(""));

    auto package3 = std::make_unique<NiceMock<PackageMock>>();
    EXPECT_CALL(*package3, get_repo_id()).WillRepeatedly(Return("repo3"));
    EXPECT_CALL(*package3, get_location()).WillOnce(Return("another/dir/file.here"));
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
    EXPECT_CALL(Const(packages), get()).WillRepeatedly(ReturnPointee(&package_map));

    NiceMock<ManifestMock> manifest;
    EXPECT_CALL(manifest, get_document()).WillOnce(Return("my-manifest"));
    EXPECT_CALL(Const(manifest), get_version()).WillOnce(ReturnPointee(&version));
    EXPECT_CALL(Const(manifest), get_packages()).WillOnce(ReturnPointee(&packages));
    EXPECT_CALL(Const(manifest), get_repositories()).WillOnce(ReturnPointee(&repositories));

    SerializerFactory serializer_factory;
    auto serializer = serializer_factory.create();
    serializer->serialize_manifest(manifest, file_path);

    std::ifstream output_file(file_path);
    std::stringstream read_file_buffer;
    read_file_buffer << output_file.rdbuf();

    EXPECT_EQ(read_file_buffer.str(), simple_manifest_yaml);
}

}