#include "impl/libpkgmanifest/mocks/objects/nevra/nevramock.hpp"
#include "impl/libpkgmanifest/mocks/objects/package/packagemock.hpp"
#include "impl/libpkgmanifest/mocks/objects/packages/packagesmock.hpp"
#include "impl/libpkgmanifest/mocks/objects/repositories/repositoriesmock.hpp"
#include "impl/libpkgmanifest/mocks/objects/repository/repositorymock.hpp"

#include "impl/libpkgmanifest/operations/packagerepositorybinder.hpp"

#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal;

using ::testing::AnyNumber;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::ReturnPointee;
using ::testing::Test;

class PackageRepositoryBinderTest : public Test {
protected:
    virtual void SetUp() {
        auto package1_wrapper = std::make_unique<NiceMock<PackageMock>>();
        package1 = package1_wrapper.get();
        std::vector<std::unique_ptr<IPackage>> arch1_pkgs;
        arch1_pkgs.push_back(std::move(package1_wrapper));

        auto package2_wrapper = std::make_unique<NiceMock<PackageMock>>();
        package2 = package2_wrapper.get();
        std::vector<std::unique_ptr<IPackage>> arch2_pkgs;
        arch2_pkgs.push_back(std::move(package2_wrapper));

        packages_map["arch1"] = std::move(arch1_pkgs);
        packages_map["arch2"] = std::move(arch2_pkgs);

        EXPECT_CALL(Const(*package1), get_nevra()).Times(AnyNumber()).WillOnce(ReturnPointee(&nevra1));
        EXPECT_CALL(Const(*package2), get_nevra()).Times(AnyNumber()).WillOnce(ReturnPointee(&nevra2));
        EXPECT_CALL(packages, get()).Times(AnyNumber()).WillOnce(ReturnPointee(&packages_map));
        EXPECT_CALL(Const(packages), get()).Times(AnyNumber()).WillOnce(ReturnPointee(&packages_map));
        EXPECT_CALL(Const(repositories), get()).WillRepeatedly(ReturnPointee(&repository_map));
        binder = std::make_unique<PackageRepositoryBinder>();
    }

    NiceMock<NevraMock> nevra1;
    NiceMock<NevraMock> nevra2;
    NiceMock<PackageMock> * package1;
    NiceMock<PackageMock> * package2;
    NiceMock<PackagesMock> packages;
    NiceMock<RepositoriesMock> repositories;
    std::map<std::string, std::unique_ptr<IRepository>> repository_map;
    std::map<std::string, std::vector<std::unique_ptr<IPackage>>> packages_map;

    std::unique_ptr<PackageRepositoryBinder> binder;
};

TEST_F(PackageRepositoryBinderTest, ValidateThrowsAnExceptionWhenNoRepositoryWithSuchPackageRepoIdExists) {
    EXPECT_CALL(*package1, get_repo_id()).WillOnce(Return("repo1"));
    EXPECT_THROW(binder->validate(repositories, *package1), PackageRepositoryBinderIdNotFoundError);
}

TEST_F(PackageRepositoryBinderTest, ValidateThrowsAnExceptionWhenAnyPackageIsMissingAMatchingRepository) {
    repository_map["repo_id"] = std::make_unique<NiceMock<RepositoryMock>>();
    EXPECT_CALL(*package1, get_repo_id()).WillOnce(Return("repo_id"));
    EXPECT_CALL(*package2, get_repo_id()).WillOnce(Return("different_repo_id"));
    EXPECT_THROW(binder->validate(repositories, packages), PackageRepositoryBinderIdNotFoundError);
}

TEST_F(PackageRepositoryBinderTest, ValidatePassesWhenPackageRepoIdExists) {
    repository_map["repo_id"] = std::make_unique<NiceMock<RepositoryMock>>();
    EXPECT_CALL(*package1, get_repo_id()).WillOnce(Return("repo_id"));
    binder->validate(repositories, *package1);
}

TEST_F(PackageRepositoryBinderTest, ValidatePassesWhenForAllPackagesThereIsAMatchingRepository) {
    repository_map["repo1"] = std::make_unique<NiceMock<RepositoryMock>>();
    repository_map["repo2"] = std::make_unique<NiceMock<RepositoryMock>>();
    EXPECT_CALL(*package1, get_repo_id()).WillOnce(Return("repo1"));
    EXPECT_CALL(*package2, get_repo_id()).WillOnce(Return("repo2"));
    binder->validate(repositories, packages);
}

TEST_F(PackageRepositoryBinderTest, BindThrowsAnExceptionWhenNoRepositoryWithSuchPackageRepoIdExists) {
    EXPECT_CALL(*package1, get_repo_id()).WillOnce(Return("repo1"));
    EXPECT_THROW(binder->bind(repositories, *package1), PackageRepositoryBinderIdNotFoundError);
}

TEST_F(PackageRepositoryBinderTest, BindThrowsAnExceptionWhenAnyPackageIsMissingAMatchingRepository) {
    repository_map["repo_id"] = std::make_unique<NiceMock<RepositoryMock>>();
    EXPECT_CALL(*package1, get_repo_id()).WillOnce(Return("repo_id"));
    EXPECT_CALL(*package2, get_repo_id()).WillOnce(Return("different_repo_id"));
    EXPECT_THROW(binder->bind(repositories, packages), PackageRepositoryBinderIdNotFoundError);
}

TEST_F(PackageRepositoryBinderTest, BindSetsTheRepositoryToThePackage) {
    auto repository = std::make_unique<NiceMock<RepositoryMock>>();
    auto repository_ptr = repository.get();

    repository_map["repo_id"] = std::move(repository);

    EXPECT_CALL(*package1, get_repo_id()).WillOnce(Return("repo_id"));
    EXPECT_CALL(*package1, set_repository(Ref(*repository_ptr)));
    binder->bind(repositories, *package1);
}

TEST_F(PackageRepositoryBinderTest, BindSetsTheRepositoriesToThePackages) {
    auto repository1 = std::make_unique<NiceMock<RepositoryMock>>();
    auto repository1_ptr = repository1.get();

    auto repository2 = std::make_unique<NiceMock<RepositoryMock>>();
    auto repository2_ptr = repository2.get();

    repository_map["repo1"] = std::move(repository1);
    repository_map["repo2"] = std::move(repository2);

    EXPECT_CALL(*package1, get_repo_id()).WillOnce(Return("repo1"));
    EXPECT_CALL(*package2, get_repo_id()).WillOnce(Return("repo2"));
    EXPECT_CALL(*package1, set_repository(Ref(*repository1_ptr)));
    EXPECT_CALL(*package2, set_repository(Ref(*repository2_ptr)));
    binder->bind(repositories, packages);
}

}