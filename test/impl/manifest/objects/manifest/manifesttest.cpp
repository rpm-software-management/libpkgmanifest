// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/common/mocks/objects/repositories/repositoriesmock.hpp"
#include "impl/manifest/mocks/objects/packages/packagesmock.hpp"
#include "impl/manifest/mocks/operations/packagerepositorybindermock.hpp"
#include "impl/manifest/objects/manifest/manifest.hpp"
#include "impl/manifest/objects/manifest/manifestfactory.hpp"

#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal::manifest;

using ::testing::Matcher;
using ::testing::NiceMock;
using ::testing::Ref;
using ::testing::Return;

Manifest create_manifest() {
    return Manifest();
}

TEST(ManifestTest, ConstantMetadataIsReturned) {
    Manifest manifest;
    EXPECT_EQ(MANIFEST_DOCUMENT_ID, manifest.get_document());
    EXPECT_EQ(MANIFEST_DOCUMENT_VERSION.get_major(), manifest.get_version().get_major());
    EXPECT_EQ(MANIFEST_DOCUMENT_VERSION.get_minor(), manifest.get_version().get_minor());
    EXPECT_EQ(MANIFEST_DOCUMENT_VERSION.get_patch(), manifest.get_version().get_patch());
}

TEST(ManifestTest, SetPackagesObjectIsReturned) {
    auto packages = std::make_unique<NiceMock<PackagesMock>>();
    auto packages_ptr = packages.get();

    auto manifest = create_manifest();
    manifest.set_packages(std::move(packages));

    EXPECT_EQ(packages_ptr, &manifest.get_packages());

    const auto & const_manifest = manifest;
    EXPECT_EQ(packages_ptr, &const_manifest.get_packages());
}

TEST(ManifestTest, SetRepositoriesObjectIsReturned) {
    auto repositories = std::make_unique<NiceMock<RepositoriesMock>>();
    auto repositories_ptr = repositories.get();

    auto manifest = create_manifest();
    manifest.set_repositories(std::move(repositories));

    EXPECT_EQ(repositories_ptr, &manifest.get_repositories());

    const auto & const_manifest = manifest;
    EXPECT_EQ(repositories_ptr, &const_manifest.get_repositories());
}

TEST(ManifestTest, ClonedObjectHasSameValuesAsOriginal) {
    // TODO(jkolarik): Tests cloned packages objects are the same
    // TODO(jkolarik): Tests cloned repositories objects are the same

    auto packages = std::make_unique<NiceMock<PackagesMock>>();
    auto cloned_packages = std::make_unique<NiceMock<PackagesMock>>();
    auto repositories = std::make_unique<NiceMock<RepositoriesMock>>();
    auto cloned_repositories = std::make_unique<NiceMock<RepositoriesMock>>();
    Manifest manifest;
    manifest.set_packages(std::move(packages));
    manifest.set_repositories(std::move(repositories));

    auto clone(manifest.clone());
    EXPECT_EQ(manifest.get_document(), clone->get_document());
    EXPECT_EQ(manifest.get_version().get_major(), clone->get_version().get_major());
}

TEST(ManifestTest, CloneAttachesClonedPackagesToTheClonedRepositoriesUsingBinder) {
    auto packages = std::make_unique<NiceMock<PackagesMock>>();
    auto cloned_packages = std::make_unique<NiceMock<PackagesMock>>();
    auto cloned_packages_ptr = cloned_packages.get();
    auto repositories = std::make_unique<NiceMock<RepositoriesMock>>();
    auto cloned_repositories = std::make_unique<NiceMock<RepositoriesMock>>();
    auto cloned_repositories_ptr = cloned_repositories.get();

    EXPECT_CALL(*packages, clone()).WillOnce(Return(std::move(cloned_packages)));
    EXPECT_CALL(*repositories, clone()).WillOnce(Return(std::move(cloned_repositories)));

    auto binder = std::make_shared<NiceMock<PackageRepositoryBinderMock>>();

    Manifest manifest;
    manifest.set_packages(std::move(packages));
    manifest.set_repositories(std::move(repositories));
    manifest.set_package_repository_binder(binder);

    EXPECT_CALL(*binder, bind(Ref(*cloned_repositories_ptr), Matcher<IPackages &>(Ref(*cloned_packages_ptr))));
    manifest.clone();
}

}  // namespace
