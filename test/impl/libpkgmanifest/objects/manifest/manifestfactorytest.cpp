#include "libpkgmanifest/mocks/objects/packages/packagesmock.hpp"
#include "libpkgmanifest/mocks/objects/packages/packagesfactorymock.hpp"
#include "libpkgmanifest/mocks/objects/version/versionmock.hpp"
#include "libpkgmanifest/mocks/objects/version/versionfactorymock.hpp"

#include "libpkgmanifest/objects/manifest/manifestfactory.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal;

using ::testing::NiceMock;
using ::testing::Return;
using ::testing::Test;

class ManifestFactoryTest : public Test {
protected:
    virtual void SetUp() {
        auto packages_wrapper = std::make_unique<NiceMock<PackagesMock>>();
        packages = packages_wrapper.get();

        auto version_wrapper = std::make_unique<NiceMock<VersionMock>>();
        version = version_wrapper.get();

        auto packages_factory = std::make_shared<NiceMock<PackagesFactoryMock>>();
        EXPECT_CALL(*packages_factory, create()).WillOnce(Return(std::move(packages_wrapper)));

        auto version_factory = std::make_shared<NiceMock<VersionFactoryMock>>();
        EXPECT_CALL(*version_factory, create()).WillOnce(Return(std::move(version_wrapper)));

        factory = std::make_unique<ManifestFactory>(packages_factory, version_factory);
    }

    NiceMock<PackagesMock> * packages;
    NiceMock<VersionMock> * version;

    std::unique_ptr<ManifestFactory> factory;
};

TEST_F(ManifestFactoryTest, CreateReturnsAnObjectWithAnInstanceOfPackagesAndVersion) {
    auto manifest = factory->create();
    EXPECT_EQ(&manifest->get_packages(), packages);
    EXPECT_EQ(&manifest->get_version(), version);
}

TEST_F(ManifestFactoryTest, CreatedObjectReturnsDocumentIdConstant) {
    auto manifest = factory->create();
    EXPECT_EQ(DOCUMENT_ID, manifest->get_document());
}

TEST_F(ManifestFactoryTest, CreatedObjectReturnsDocumentVersionConstant) {
    EXPECT_CALL(*version, set_major(DOCUMENT_VERSION_MAJOR));
    EXPECT_CALL(*version, set_minor(DOCUMENT_VERSION_MINOR));
    EXPECT_CALL(*version, set_patch(DOCUMENT_VERSION_PATCH));

    auto manifest = factory->create();
}

}