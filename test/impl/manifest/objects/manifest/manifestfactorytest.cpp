// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/common/mocks/objects/repositories/repositoriesfactorymock.hpp"
#include "impl/common/mocks/objects/repositories/repositoriesmock.hpp"
#include "impl/manifest/mocks/objects/packages/packagesfactorymock.hpp"
#include "impl/manifest/mocks/objects/packages/packagesmock.hpp"
#include "impl/manifest/mocks/operations/packagerepositorybindermock.hpp"
#include "impl/manifest/objects/manifest/manifestfactory.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal::manifest;

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

        auto packages_factory = std::make_shared<NiceMock<PackagesFactoryMock>>();
        EXPECT_CALL(*packages_factory, create()).WillOnce(Return(std::move(packages_wrapper)));

        auto repositories_factory = std::make_shared<NiceMock<RepositoriesFactoryMock>>();
        EXPECT_CALL(*repositories_factory, create()).WillOnce(Return(std::move(repositories_wrapper)));

        auto binder = std::make_shared<NiceMock<PackageRepositoryBinderMock>>();
        factory = std::make_unique<ManifestFactory>(packages_factory, repositories_factory, binder);
    }

    NiceMock<PackagesMock> * packages;
    NiceMock<RepositoriesMock> * repositories;

    std::unique_ptr<ManifestFactory> factory;
};

TEST_F(ManifestFactoryTest, CreateReturnsAnObjectWithAnInstanceOfPackagesRepositoriesAndBinder) {
    auto manifest = factory->create();
    EXPECT_EQ(&manifest->get_packages(), packages);
    EXPECT_EQ(&manifest->get_repositories(), repositories);
}

TEST_F(ManifestFactoryTest, CreatedObjectReturnsDocumentIdConstant) {
    auto manifest = factory->create();
    EXPECT_EQ(MANIFEST_DOCUMENT_ID, manifest->get_document());
}

TEST_F(ManifestFactoryTest, CreatedObjectReturnsDocumentVersionConstant) {
    auto manifest = factory->create();
    EXPECT_EQ(MANIFEST_DOCUMENT_VERSION.get_major(), manifest->get_version().get_major());
    EXPECT_EQ(MANIFEST_DOCUMENT_VERSION.get_minor(), manifest->get_version().get_minor());
    EXPECT_EQ(MANIFEST_DOCUMENT_VERSION.get_patch(), manifest->get_version().get_patch());
}

}  // namespace
