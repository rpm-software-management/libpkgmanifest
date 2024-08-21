#include "libpkgmanifest/mocks/objects/packages/packagesmock.hpp"
#include "libpkgmanifest/mocks/objects/version/versionmock.hpp"

#include "libpkgmanifest/objects/manifest/manifest.hpp"

#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal;

using ::testing::NiceMock;
using ::testing::Return;

TEST(ManifestTest, DefaultDocumentIsEmpty) {
    EXPECT_EQ(std::string(), Manifest().get_document());
}

TEST(ManifestTest, DefaultVersionIsNull) {
    EXPECT_EQ(nullptr, &Manifest().get_version());
}

TEST(ManifestTest, DefaultPackagesIsNull) {
    EXPECT_EQ(nullptr, &Manifest().get_packages());
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

TEST(ManifestTest, ClonedObjectHasSameValuesAsOriginal) {
    // TODO: Tests cloned packages objects are the same

    auto packages = std::make_unique<NiceMock<PackagesMock>>();
    auto cloned_packages = std::make_unique<NiceMock<PackagesMock>>();
    auto version = std::make_unique<NiceMock<VersionMock>>();
    auto cloned_version = std::make_unique<NiceMock<VersionMock>>();
    EXPECT_CALL(*version, get_major()).WillOnce(Return(7));
    EXPECT_CALL(*cloned_version, get_major()).WillOnce(Return(7));
    EXPECT_CALL(*version, clone()).WillOnce(Return(std::move(cloned_version)));

    Manifest manifest;
    manifest.set_document("doc1");
    manifest.set_version(std::move(version));
    manifest.set_packages(std::move(packages));

    auto clone(manifest.clone());
    EXPECT_EQ(manifest.get_document(), clone->get_document());
    EXPECT_EQ(manifest.get_version().get_major(), clone->get_version().get_major());
}

}