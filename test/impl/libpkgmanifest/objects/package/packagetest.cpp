#include "impl/libpkgmanifest/mocks/objects/checksum/checksummock.hpp"
#include "impl/libpkgmanifest/mocks/objects/module/modulemock.hpp"
#include "impl/libpkgmanifest/mocks/objects/nevra/nevramock.hpp"
#include "impl/libpkgmanifest/mocks/objects/repository/repositorymock.hpp"

#include "impl/libpkgmanifest/objects/package/package.hpp"

#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal;

using ::testing::NiceMock;
using ::testing::Ref;
using ::testing::Return;
using ::testing::ReturnPointee;

TEST(PackageTest, DefaultRepoIdIsEmpty) {
    EXPECT_EQ(std::string(), Package().get_repo_id());
}

TEST(PackageTest, DefaultLocationIsEmpty) {
    EXPECT_EQ(std::string(), Package().get_location());
}

TEST(PackageTest, DefaultSizeIsZero) {
    EXPECT_EQ(0, Package().get_size());
}

TEST(PackageTest, DefaultChecksumIsNull) {
    EXPECT_EQ(nullptr, &Package().get_checksum());
}

TEST(PackageTest, DefaultNevraIsNull) {
    EXPECT_EQ(nullptr, &Package().get_nevra());
}

TEST(PackageTest, DefaultSrpmIsNull) {
    EXPECT_EQ(nullptr, &Package().get_srpm());
}

TEST(PackageTest, DefaultModuleIsNull) {
    EXPECT_EQ(nullptr, &Package().get_module());
}

TEST(PackageTest, SetRepoIdIsReturned) {
    Package package;
    package.set_repo_id("repo1");
    EXPECT_EQ("repo1", package.get_repo_id());
}

TEST(PackageTest, SetLocationIsReturned) {
    Package package;
    package.set_location("location");
    EXPECT_EQ("location", package.get_location());
}

TEST(PackageTest, SetSizeIsReturned) {
    Package package;
    package.set_size(5678U);
    EXPECT_EQ(5678U, package.get_size());
}

TEST(PackageTest, SetChecksumObjectIsReturned) {
    auto checksum = std::make_unique<NiceMock<ChecksumMock>>();
    auto checksum_ptr = checksum.get();

    Package package;
    package.set_checksum(std::move(checksum));

    EXPECT_EQ(checksum_ptr, &package.get_checksum());

    const auto & const_package = package;
    EXPECT_EQ(checksum_ptr, &const_package.get_checksum());
}

TEST(PackageTest, SetNevraObjectIsReturned) {
    auto nevra = std::make_unique<NiceMock<NevraMock>>();
    auto nevra_ptr = nevra.get();

    Package package;
    package.set_nevra(std::move(nevra));

    EXPECT_EQ(nevra_ptr, &package.get_nevra());

    const auto & const_package = package;
    EXPECT_EQ(nevra_ptr, &const_package.get_nevra());
}

TEST(PackageTest, SetSrpmObjectIsReturned) {
    auto nevra = std::make_unique<NiceMock<NevraMock>>();
    auto nevra_ptr = nevra.get();

    Package package;
    package.set_srpm(std::move(nevra));

    EXPECT_EQ(nevra_ptr, &package.get_srpm());

    const auto & const_package = package;
    EXPECT_EQ(nevra_ptr, &const_package.get_srpm());
}

TEST(PackageTest, SetModuleObjectIsReturned) {
    auto module = std::make_unique<NiceMock<ModuleMock>>();
    auto module_ptr = module.get();

    Package package;
    package.set_module(std::move(module));

    EXPECT_EQ(module_ptr, &package.get_module());

    const auto & const_package = package;
    EXPECT_EQ(module_ptr, &const_package.get_module());
}

TEST(PackageTest, GetRepositoryThrowsAnExceptionWhenRepositoryNotSet) {
    Package package;
    package.set_nevra(std::make_unique<NiceMock<NevraMock>>());
    EXPECT_THROW(package.get_repository(), PackageRepositoryNotAttachedError);
}

TEST(PackageTest, GetUrlThrowsAnExceptionWhenRepositoryNotSet) {
    Package package;
    package.set_nevra(std::make_unique<NiceMock<NevraMock>>());
    EXPECT_THROW(package.get_url(), PackageRepositoryNotAttachedError);
}

TEST(PackageTest, AfterSetRepositoryGetRepositoryReturnsTheCorrespondingRepository) {
    NiceMock<RepositoryMock> repository;

    Package package;
    package.set_repository(repository);

    EXPECT_EQ(&repository, &package.get_repository());

    const auto & const_package = package;
    EXPECT_EQ(&repository, &const_package.get_repository());
}

TEST(PackageTest, AfterSetRepositoryUrlReturnsAFullPathToThePackage) {
    NiceMock<RepositoryMock> repository;
    EXPECT_CALL(repository, get_url()).WillOnce(Return("http://server.org/folder/"));

    Package package;
    package.set_repo_id("id1");
    package.set_location("pkg/package.rpm");
    package.set_repository(repository);

    EXPECT_EQ("http://server.org/folder/pkg/package.rpm", package.get_url());
}

TEST(PackageTest, AfterSetRepositoryUrlAddsAMissingSlashBetweenTheRepositoryUrlAndLocationParts) {
    NiceMock<RepositoryMock> repository;
    EXPECT_CALL(repository, get_url()).WillOnce(Return("http://server.org/folder"));

    Package package;
    package.set_repo_id("id1");
    package.set_location("pkg/package.rpm");
    package.set_repository(repository);

    EXPECT_EQ("http://server.org/folder/pkg/package.rpm", package.get_url());
}

TEST(PackageTest, AfterSetRepositoryUrlSubstitutesTheArchInThePath) {
    NiceMock<RepositoryMock> repository;
    EXPECT_CALL(repository, get_url()).WillOnce(Return("http://server.org/$arch/packages"));

    auto nevra = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*nevra, get_arch()).WillOnce(Return("i686"));

    Package package;
    package.set_nevra(std::move(nevra));
    package.set_repo_id("repo1");
    package.set_location("p/package.rpm");
    package.set_repository(repository);

    EXPECT_EQ("http://server.org/i686/packages/p/package.rpm", package.get_url());
}

TEST(PackageTest, ClonedUnattachedObjectHasSameValuesAsOriginal) {
    auto checksum = std::make_unique<NiceMock<ChecksumMock>>();
    auto cloned_checksum = std::make_unique<NiceMock<ChecksumMock>>();
    EXPECT_CALL(*checksum, get_digest()).WillOnce(Return("same_digest"));
    EXPECT_CALL(*cloned_checksum, get_digest()).WillOnce(Return("same_digest"));
    EXPECT_CALL(*checksum, clone()).WillOnce(Return(std::move(cloned_checksum)));

    auto nevra = std::make_unique<NiceMock<NevraMock>>();
    auto cloned_nevra = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*nevra, get_name()).WillOnce(Return("same_package"));
    EXPECT_CALL(*cloned_nevra, get_name()).WillOnce(Return("same_package"));
    EXPECT_CALL(*nevra, clone()).WillOnce(Return(std::move(cloned_nevra)));

    auto srpm = std::make_unique<NiceMock<NevraMock>>();
    auto cloned_srpm = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*srpm, get_name()).WillOnce(Return("same_source"));
    EXPECT_CALL(*cloned_srpm, get_name()).WillOnce(Return("same_source"));
    EXPECT_CALL(*srpm, clone()).WillOnce(Return(std::move(cloned_srpm)));

    auto module = std::make_unique<NiceMock<ModuleMock>>();
    auto cloned_module = std::make_unique<NiceMock<ModuleMock>>();
    EXPECT_CALL(*module, get_name()).WillOnce(Return("same_name"));
    EXPECT_CALL(*cloned_module, get_name()).WillOnce(Return("same_name"));
    EXPECT_CALL(*module, clone()).WillOnce(Return(std::move(cloned_module)));

    Package package;
    package.set_repo_id("id1234");
    package.set_location("loc123");
    package.set_size(1979843615U);
    package.set_checksum(std::move(checksum));
    package.set_nevra(std::move(nevra));
    package.set_srpm(std::move(srpm));
    package.set_module(std::move(module));

    auto clone(package.clone());
    EXPECT_EQ(package.get_repo_id(), clone->get_repo_id());
    EXPECT_EQ(package.get_location(), clone->get_location());
    EXPECT_EQ(package.get_size(), clone->get_size());
    EXPECT_EQ(package.get_checksum().get_digest(), clone->get_checksum().get_digest());
    EXPECT_EQ(package.get_nevra().get_name(), clone->get_nevra().get_name());
    EXPECT_EQ(package.get_srpm().get_name(), clone->get_srpm().get_name());
    EXPECT_EQ(package.get_module().get_name(), clone->get_module().get_name());
}

TEST(PackageTest, ClonedAttachedObjectHasSameValuesAsOriginal) {
    NiceMock<RepositoryMock> repository;
    EXPECT_CALL(repository, get_id()).WillRepeatedly(Return("id1234"));
    EXPECT_CALL(repository, get_url()).WillRepeatedly(Return("http://server.org/folder"));

    auto checksum = std::make_unique<NiceMock<ChecksumMock>>();
    auto cloned_checksum = std::make_unique<NiceMock<ChecksumMock>>();
    EXPECT_CALL(*checksum, get_digest()).WillOnce(Return("same_digest"));
    EXPECT_CALL(*cloned_checksum, get_digest()).WillOnce(Return("same_digest"));
    EXPECT_CALL(*checksum, clone()).WillOnce(Return(std::move(cloned_checksum)));

    auto nevra = std::make_unique<NiceMock<NevraMock>>();
    auto cloned_nevra = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*nevra, get_name()).WillOnce(Return("same_package"));
    EXPECT_CALL(*cloned_nevra, get_name()).WillOnce(Return("same_package"));
    EXPECT_CALL(*nevra, clone()).WillOnce(Return(std::move(cloned_nevra)));

    auto srpm = std::make_unique<NiceMock<NevraMock>>();
    auto cloned_srpm = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*srpm, get_name()).WillOnce(Return("same_source"));
    EXPECT_CALL(*cloned_srpm, get_name()).WillOnce(Return("same_source"));
    EXPECT_CALL(*srpm, clone()).WillOnce(Return(std::move(cloned_srpm)));

    auto module = std::make_unique<NiceMock<ModuleMock>>();
    auto cloned_module = std::make_unique<NiceMock<ModuleMock>>();
    EXPECT_CALL(*module, get_name()).WillOnce(Return("same_name"));
    EXPECT_CALL(*cloned_module, get_name()).WillOnce(Return("same_name"));
    EXPECT_CALL(*module, clone()).WillOnce(Return(std::move(cloned_module)));

    Package package;
    package.set_repo_id("id1234");
    package.set_location("loc123");
    package.set_size(1979843615U);
    package.set_checksum(std::move(checksum));
    package.set_nevra(std::move(nevra));
    package.set_srpm(std::move(srpm));
    package.set_module(std::move(module));
    package.set_repository(repository);

    auto clone(package.clone());
    EXPECT_EQ(package.get_repo_id(), clone->get_repo_id());
    EXPECT_EQ(package.get_location(), clone->get_location());
    EXPECT_EQ(package.get_url(), clone->get_url());
    EXPECT_EQ(package.get_size(), clone->get_size());
    EXPECT_EQ(package.get_repository().get_id(), clone->get_repository().get_id());
    EXPECT_EQ(package.get_repository().get_url(), clone->get_repository().get_url());
    EXPECT_EQ(package.get_checksum().get_digest(), clone->get_checksum().get_digest());
    EXPECT_EQ(package.get_nevra().get_name(), clone->get_nevra().get_name());
    EXPECT_EQ(package.get_srpm().get_name(), clone->get_srpm().get_name());
    EXPECT_EQ(package.get_module().get_name(), clone->get_module().get_name());
}

}