#include "impl/libpkgmanifest/mocks/objects/packages/packagesmock.hpp"
#include "impl/libpkgmanifest/mocks/objects/packages/packagesfactorymock.hpp"
#include "impl/libpkgmanifest/mocks/objects/repositories/repositoriesmock.hpp"
#include "impl/libpkgmanifest/mocks/objects/repositories/repositoriesfactorymock.hpp"
#include "impl/libpkgmanifest/mocks/objects/version/versionmock.hpp"
#include "impl/libpkgmanifest/mocks/objects/version/versionfactorymock.hpp"
#include "impl/libpkgmanifest/mocks/operations/packagerepositorybindermock.hpp"

#include "impl/libpkgmanifest/objects/manifest/manifestfactory.hpp"

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

        auto repositories_wrapper = std::make_unique<NiceMock<RepositoriesMock>>();
        repositories = repositories_wrapper.get();

        auto version_wrapper = std::make_unique<NiceMock<VersionMock>>();
        version = version_wrapper.get();

        auto packages_factory = std::make_shared<NiceMock<PackagesFactoryMock>>();
        EXPECT_CALL(*packages_factory, create()).WillOnce(Return(std::move(packages_wrapper)));

        auto repositories_factory = std::make_shared<NiceMock<RepositoriesFactoryMock>>();
        EXPECT_CALL(*repositories_factory, create()).WillOnce(Return(std::move(repositories_wrapper)));

        auto version_factory = std::make_shared<NiceMock<VersionFactoryMock>>();
        EXPECT_CALL(*version_factory, create()).WillOnce(Return(std::move(version_wrapper)));

        auto binder = std::make_shared<NiceMock<PackageRepositoryBinderMock>>();
        factory = std::make_unique<ManifestFactory>(packages_factory, repositories_factory, version_factory, binder);
    }

    NiceMock<PackagesMock> * packages;
    NiceMock<RepositoriesMock> * repositories;
    NiceMock<VersionMock> * version;

    std::unique_ptr<ManifestFactory> factory;
};

TEST_F(ManifestFactoryTest, CreateReturnsAnObjectWithAnInstanceOfPackagesRepositoriesVersionBinder) {
    auto manifest = factory->create();
    EXPECT_EQ(&manifest->get_packages(), packages);
    EXPECT_EQ(&manifest->get_repositories(), repositories);
    EXPECT_EQ(&manifest->get_version(), version);
}

TEST_F(ManifestFactoryTest, CreatedObjectReturnsDocumentIdConstant) {
    auto manifest = factory->create();
    EXPECT_EQ(MANIFEST_DOCUMENT_ID, manifest->get_document());
}

TEST_F(ManifestFactoryTest, CreatedObjectReturnsDocumentVersionConstant) {
    EXPECT_CALL(*version, set_major(MANIFEST_DOCUMENT_VERSION_MAJOR));
    EXPECT_CALL(*version, set_minor(MANIFEST_DOCUMENT_VERSION_MINOR));
    EXPECT_CALL(*version, set_patch(MANIFEST_DOCUMENT_VERSION_PATCH));

    auto manifest = factory->create();
}

}