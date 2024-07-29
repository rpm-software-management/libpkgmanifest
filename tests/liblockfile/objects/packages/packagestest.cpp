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
}

TEST(PackagesTest, AddedPackageIsReturnedByItsArch) {
    auto package = std::make_unique<NiceMock<PackageMock>>();
    auto package_ptr = package.get();

    Packages packages;

    EXPECT_CALL(*package_ptr, get_arch()).WillOnce(Return("arch"));
    packages.add(std::move(package));

    auto & packages_vector = packages.get("arch");
    EXPECT_EQ(1, packages_vector.size());
    EXPECT_EQ(package_ptr, packages_vector[0].get());
}

}