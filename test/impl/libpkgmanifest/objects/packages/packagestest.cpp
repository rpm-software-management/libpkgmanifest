#include "impl/libpkgmanifest/mocks/objects/nevra/nevramock.hpp"
#include "impl/libpkgmanifest/mocks/objects/package/packagemock.hpp"

#include "impl/libpkgmanifest/objects/packages/packages.hpp"

#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal;

using ::testing::NiceMock;
using ::testing::Return;

TEST(PackagesTest, DefaultPackagesAreEmpty) {
    EXPECT_EQ(0, Packages().get().size());
}

TEST(PackagesTest, AddedPackageIsReturned) {
    auto nevra = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*nevra, get_arch()).WillOnce(Return("arch"));

    auto package = std::make_unique<NiceMock<PackageMock>>();
    auto package_ptr = package.get();
    EXPECT_CALL(*package, get_nevra()).WillOnce(ReturnPointee(nevra.get()));

    Packages packages;
    packages.add(std::move(package));

    auto & packages_map = packages.get();
    EXPECT_EQ(1, packages_map.size());
    EXPECT_EQ(package_ptr, packages_map.begin()->second[0].get());

    const auto & const_packages_map = packages_map;
    EXPECT_EQ(1, const_packages_map.size());
    EXPECT_EQ(package_ptr, const_packages_map.begin()->second[0].get());
}

TEST(PackagesTest, AddedPackageIsReturnedByItsArch) {
    auto nevra = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*nevra, get_arch()).WillOnce(Return("arch"));

    auto package = std::make_unique<NiceMock<PackageMock>>();
    auto package_ptr = package.get();
    EXPECT_CALL(*package, get_nevra()).WillOnce(ReturnPointee(nevra.get()));

    Packages packages;
    packages.add(std::move(package));

    auto & packages_map = packages.get();
    auto & arch_packages = packages_map.at("arch");
    EXPECT_EQ(1, arch_packages.size());
    EXPECT_EQ(package_ptr, arch_packages[0].get());
}

TEST(PackagesTest, ContainsReturnsFalseWhenNoPackages) {
    NiceMock<NevraMock> nevra;
    EXPECT_CALL(nevra, get_arch()).WillOnce(Return("arch"));

    NiceMock<PackageMock> package;
    EXPECT_CALL(Const(package), get_nevra()).WillOnce(ReturnPointee(&nevra));

    Packages packages;
    EXPECT_FALSE(packages.contains(package));
}

TEST(PackagesTest, ContainsReturnsTrueWhenPackageWithSameNevraAndRepoIdIsPresent) {
    auto existing_nevra = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*existing_nevra, get_arch()).WillOnce(Return("arch"));
    EXPECT_CALL(*existing_nevra, to_string()).WillOnce(Return("12345"));

    auto existing_package = std::make_unique<NiceMock<PackageMock>>();
    EXPECT_CALL(*existing_package, get_nevra()).WillRepeatedly(ReturnPointee(existing_nevra.get()));
    EXPECT_CALL(*existing_package, get_repo_id()).WillOnce(Return("repo1"));

    auto checked_nevra = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*checked_nevra, get_arch()).WillOnce(Return("arch"));
    EXPECT_CALL(*checked_nevra, to_string()).WillOnce(Return("12345"));

    auto checked_package = std::make_unique<NiceMock<PackageMock>>();
    EXPECT_CALL(Const(*checked_package), get_nevra()).WillRepeatedly(ReturnPointee(checked_nevra.get()));
    EXPECT_CALL(*checked_package, get_repo_id()).WillOnce(Return("repo1"));

    Packages packages;
    packages.add(std::move(existing_package));
    EXPECT_TRUE(packages.contains(*checked_package));
}

TEST(PackagesTest, ContainsReturnsFalseWhenPackageWithDifferentNevraIsPresent) {
    auto existing_nevra = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*existing_nevra, get_arch()).WillOnce(Return("arch"));
    EXPECT_CALL(*existing_nevra, to_string()).WillOnce(Return("12345"));

    auto existing_package = std::make_unique<NiceMock<PackageMock>>();
    EXPECT_CALL(*existing_package, get_nevra()).WillRepeatedly(ReturnPointee(existing_nevra.get()));

    auto checked_nevra = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*checked_nevra, get_arch()).WillOnce(Return("arch"));
    EXPECT_CALL(*checked_nevra, to_string()).WillOnce(Return("11111"));

    auto checked_package = std::make_unique<NiceMock<PackageMock>>();
    EXPECT_CALL(Const(*checked_package), get_nevra()).WillRepeatedly(ReturnPointee(checked_nevra.get()));

    Packages packages;
    packages.add(std::move(existing_package));
    EXPECT_FALSE(packages.contains(*checked_package));
}

TEST(PackagesTest, ContainsReturnsFalseWhenPackageWithDifferentRepoIdIsPresent) {
    auto existing_nevra = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*existing_nevra, get_arch()).WillOnce(Return("arch"));
    EXPECT_CALL(*existing_nevra, to_string()).WillOnce(Return("12345"));

    auto existing_package = std::make_unique<NiceMock<PackageMock>>();
    EXPECT_CALL(*existing_package, get_nevra()).WillRepeatedly(ReturnPointee(existing_nevra.get()));
    EXPECT_CALL(*existing_package, get_repo_id()).WillOnce(Return("repo1"));

    auto checked_nevra = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*checked_nevra, get_arch()).WillOnce(Return("arch"));
    EXPECT_CALL(*checked_nevra, to_string()).WillOnce(Return("12345"));

    auto checked_package = std::make_unique<NiceMock<PackageMock>>();
    EXPECT_CALL(Const(*checked_package), get_nevra()).WillRepeatedly(ReturnPointee(checked_nevra.get()));
    EXPECT_CALL(*checked_package, get_repo_id()).WillOnce(Return("repo2"));

    Packages packages;
    packages.add(std::move(existing_package));
    EXPECT_FALSE(packages.contains(*checked_package));
}

TEST(PackagesTest, ClonedObjectHasSameValuesAsOriginal) {
    auto nevra1 = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*nevra1, get_arch()).WillOnce(Return("arch1"));
    auto package1 = std::make_unique<NiceMock<PackageMock>>();
    EXPECT_CALL(*package1, get_nevra()).WillOnce(ReturnPointee(nevra1.get()));

    auto nevra2 = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*nevra2, get_arch()).WillOnce(Return("arch2"));
    auto package2 = std::make_unique<NiceMock<PackageMock>>();
    EXPECT_CALL(*package2, get_nevra()).WillOnce(ReturnPointee(nevra2.get()));

    auto cloned_package1 = std::make_unique<NiceMock<PackageMock>>();
    auto cloned_package2 = std::make_unique<NiceMock<PackageMock>>();
    EXPECT_CALL(*package1, get_repo_id()).WillOnce(Return("repoid1"));
    EXPECT_CALL(*cloned_package1, get_repo_id()).WillOnce(Return("repoid1"));
    EXPECT_CALL(*package2, get_repo_id()).WillOnce(Return("repoid2"));
    EXPECT_CALL(*cloned_package2, get_repo_id()).WillOnce(Return("repoid2"));
    EXPECT_CALL(*package1, clone()).WillOnce(Return(std::move(cloned_package1)));
    EXPECT_CALL(*package2, clone()).WillOnce(Return(std::move(cloned_package2)));

    Packages packages;
    packages.add(std::move(package1));
    packages.add(std::move(package2));

    auto clone(packages.clone());
    EXPECT_EQ(packages.get().size(), clone->get().size());
    EXPECT_EQ(packages.get()["arch1"].size(), clone->get()["arch1"].size());
    EXPECT_EQ(packages.get()["arch1"][0]->get_repo_id(), clone->get()["arch1"][0]->get_repo_id());
    EXPECT_EQ(packages.get()["arch2"].size(), clone->get()["arch2"].size());
    EXPECT_EQ(packages.get()["arch2"][0]->get_repo_id(), clone->get()["arch2"][0]->get_repo_id());
}

}