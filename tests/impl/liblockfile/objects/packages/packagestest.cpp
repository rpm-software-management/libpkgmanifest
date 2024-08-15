#include "liblockfile/mocks/objects/package/packagemock.hpp"

#include "liblockfile/objects/packages/packages.hpp"

#include <gtest/gtest.h>

namespace {

using namespace liblockfile::internal;

using ::testing::NiceMock;
using ::testing::Return;

TEST(PackagesTest, DefaultPackagesAreEmpty) {
    EXPECT_EQ(0, Packages().get().size());
}

TEST(PackagesTest, AddedPackageIsReturned) {
    auto package = std::make_unique<NiceMock<PackageMock>>();
    auto package_ptr = package.get();

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
    auto package = std::make_unique<NiceMock<PackageMock>>();
    auto package_ptr = package.get();

    Packages packages;

    EXPECT_CALL(*package_ptr, get_arch()).WillOnce(Return("arch"));
    packages.add(std::move(package));

    auto & packages_map = packages.get();
    auto & arch_packages = packages_map.at("arch");
    EXPECT_EQ(1, arch_packages.size());
    EXPECT_EQ(package_ptr, arch_packages[0].get());
}

TEST(PackagesTest, ClonedObjectHasSameValuesAsOriginal) {
    auto package1 = std::make_unique<NiceMock<PackageMock>>();
    auto package2 = std::make_unique<NiceMock<PackageMock>>();
    auto cloned_package1 = std::make_unique<NiceMock<PackageMock>>();
    auto cloned_package2 = std::make_unique<NiceMock<PackageMock>>();
    EXPECT_CALL(*package1, get_arch()).WillOnce(Return("arch1"));
    EXPECT_CALL(*package1, get_nevra()).WillOnce(Return("pkg1"));
    EXPECT_CALL(*cloned_package1, get_nevra()).WillOnce(Return("pkg1"));
    EXPECT_CALL(*package2, get_arch()).WillOnce(Return("arch2"));
    EXPECT_CALL(*package2, get_nevra()).WillOnce(Return("pkg2"));
    EXPECT_CALL(*cloned_package2, get_nevra()).WillOnce(Return("pkg2"));
    EXPECT_CALL(*package1, clone()).WillOnce(Return(std::move(cloned_package1)));
    EXPECT_CALL(*package2, clone()).WillOnce(Return(std::move(cloned_package2)));

    Packages packages;
    packages.add(std::move(package1));
    packages.add(std::move(package2));

    auto clone(packages.clone());
    EXPECT_EQ(packages.get().size(), clone->get().size());
    EXPECT_EQ(packages.get()["arch1"].size(), clone->get()["arch1"].size());
    EXPECT_EQ(packages.get()["arch1"][0]->get_nevra(), clone->get()["arch1"][0]->get_nevra());
    EXPECT_EQ(packages.get()["arch2"].size(), clone->get()["arch2"].size());
    EXPECT_EQ(packages.get()["arch2"][0]->get_nevra(), clone->get()["arch2"][0]->get_nevra());
}

}