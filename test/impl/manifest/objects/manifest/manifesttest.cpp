// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/common/mocks/objects/repositories/repositoriesmock.hpp"
#include "impl/common/mocks/objects/version/versionmock.hpp"
#include "impl/manifest/mocks/objects/packages/packagesmock.hpp"
#include "impl/manifest/mocks/operations/packagerepositorybindermock.hpp"

#include "impl/manifest/objects/manifest/manifest.hpp"

#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal::manifest;

using ::testing::Matcher;
using ::testing::NiceMock;
using ::testing::Ref;
using ::testing::Return;

TEST(ManifestTest, DefaultDocumentIsEmpty) {
    EXPECT_EQ(std::string(), Manifest().get_document());
}

TEST(ManifestTest, SetDocumentIsReturned) {
    Manifest manifest;
    manifest.set_document("document");
    EXPECT_EQ("document", manifest.get_document());
}

TEST(ManifestTest, SetVersionObjectIsReturned) {
    auto version = std::make_unique<NiceMock<VersionMock>>();
    auto version_ptr = version.get();

    Manifest manifest;
    manifest.set_version(std::move(version));

    EXPECT_EQ(version_ptr, &manifest.get_version());

    const auto & const_manifest = manifest;
    EXPECT_EQ(version_ptr, &const_manifest.get_version());
}

TEST(ManifestTest, SetPackagesObjectIsReturned) {
    auto packages = std::make_unique<NiceMock<PackagesMock>>();
    auto packages_ptr = packages.get();

    Manifest manifest;
    manifest.set_packages(std::move(packages));

    EXPECT_EQ(packages_ptr, &manifest.get_packages());

    const auto & const_manifest = manifest;
    EXPECT_EQ(packages_ptr, &const_manifest.get_packages());
}

TEST(ManifestTest, SetRepositoriesObjectIsReturned) {
    auto repositories = std::make_unique<NiceMock<RepositoriesMock>>();
    auto repositories_ptr = repositories.get();

    Manifest manifest;
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
    auto version = std::make_unique<NiceMock<VersionMock>>();
    auto cloned_version = std::make_unique<NiceMock<VersionMock>>();
    EXPECT_CALL(*version, get_major()).WillOnce(Return(7));
    EXPECT_CALL(*cloned_version, get_major()).WillOnce(Return(7));
    EXPECT_CALL(*version, clone()).WillOnce(Return(std::move(cloned_version)));

    Manifest manifest;
    manifest.set_document("doc1");
    manifest.set_version(std::move(version));
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
    manifest.set_version(std::make_unique<NiceMock<VersionMock>>());
    manifest.set_packages(std::move(packages));
    manifest.set_repositories(std::move(repositories));
    manifest.set_package_repository_binder(binder);

    EXPECT_CALL(*binder, bind(Ref(*cloned_repositories_ptr), Matcher<IPackages &>(Ref(*cloned_packages_ptr))));
    manifest.clone();
}

}