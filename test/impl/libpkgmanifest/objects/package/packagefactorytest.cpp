#include "libpkgmanifest/mocks/objects/checksum/checksummock.hpp"
#include "libpkgmanifest/mocks/objects/checksum/checksumfactorymock.hpp"

#include "libpkgmanifest/objects/package/packagefactory.hpp"

#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal;

using ::testing::NiceMock;
using ::testing::Return;

TEST(PackageFactoryTest, CreateReturnsAnObjectWithAnInstanceOfChecksum) {
    auto checksum = std::make_unique<NiceMock<ChecksumMock>>();
    auto checksum_ptr = checksum.get();

    auto checksum_factory = std::make_shared<NiceMock<ChecksumFactoryMock>>();
    EXPECT_CALL(*checksum_factory, create()).WillOnce(Return(std::move(checksum)));

    PackageFactory package_factory(checksum_factory);
    auto package = package_factory.create();
    EXPECT_EQ(&package->get_checksum(), checksum_ptr);
}

}