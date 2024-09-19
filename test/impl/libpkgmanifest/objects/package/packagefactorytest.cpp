#include "libpkgmanifest/mocks/objects/checksum/checksummock.hpp"
#include "libpkgmanifest/mocks/objects/checksum/checksumfactorymock.hpp"
#include "libpkgmanifest/mocks/objects/module/modulemock.hpp"
#include "libpkgmanifest/mocks/objects/module/modulefactorymock.hpp"
#include "libpkgmanifest/mocks/objects/nevra/nevramock.hpp"
#include "libpkgmanifest/mocks/objects/nevra/nevrafactorymock.hpp"

#include "libpkgmanifest/objects/package/packagefactory.hpp"

#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal;

using ::testing::NiceMock;
using ::testing::Return;

TEST(PackageFactoryTest, CreateReturnsAnObjectWithAnInstanceOfChecksumNevraSrpmAndModule) {
    auto checksum = std::make_unique<NiceMock<ChecksumMock>>();
    auto checksum_ptr = checksum.get();
    auto module = std::make_unique<NiceMock<ModuleMock>>();
    auto module_ptr = module.get();
    auto nevra = std::make_unique<NiceMock<NevraMock>>();
    auto nevra_ptr = nevra.get();
    auto srpm = std::make_unique<NiceMock<NevraMock>>();
    auto srpm_ptr = srpm.get();

    auto checksum_factory = std::make_shared<NiceMock<ChecksumFactoryMock>>();
    EXPECT_CALL(*checksum_factory, create()).WillOnce(Return(std::move(checksum)));
    auto module_factory = std::make_shared<NiceMock<ModuleFactoryMock>>();
    EXPECT_CALL(*module_factory, create()).WillOnce(Return(std::move(module)));
    auto nevra_factory = std::make_shared<NiceMock<NevraFactoryMock>>();
    EXPECT_CALL(*nevra_factory, create())
        .WillOnce(Return(std::move(nevra)))
        .WillOnce(Return(std::move(srpm)));

    PackageFactory package_factory(checksum_factory, nevra_factory, module_factory);
    auto package = package_factory.create();
    EXPECT_EQ(&package->get_checksum(), checksum_ptr);
    EXPECT_EQ(&package->get_module(), module_ptr);
    EXPECT_EQ(&package->get_nevra(), nevra_ptr);
    EXPECT_EQ(&package->get_srpm(), srpm_ptr);
}

}