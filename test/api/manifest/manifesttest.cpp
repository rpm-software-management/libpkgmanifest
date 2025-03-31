#include "libpkgmanifest/manifest/manifest.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::manifest;

TEST(ApiManifestTest, SetDocument) {
    Manifest manifest;
    manifest.set_document("my-manifest");
    EXPECT_EQ(manifest.get_document(), "my-manifest");
}

TEST(ApiManifestTest, SetVersion) {
    Manifest manifest;

    Version version;
    version.set_major(6);
    version.set_minor(9);
    version.set_patch(1);

    manifest.set_version(version);

    EXPECT_EQ(manifest.get_version().get_major(), 6);
    EXPECT_EQ(manifest.get_version().get_minor(), 9);
    EXPECT_EQ(manifest.get_version().get_patch(), 1);
}

TEST(ApiManifestTest, SetPackages) {
    Manifest manifest;

    Packages packages;
    Package package1;
    package1.get_nevra().set_name("package1");
    Package package2;
    package2.get_nevra().set_name("package2");
    packages.add(package1);
    packages.add(package2);

    manifest.set_packages(packages);

    auto packages_vector = manifest.get_packages().get();
    EXPECT_EQ(packages_vector.size(), 2);
    EXPECT_EQ(packages_vector[0].get_nevra().get_name(), "package1");
    EXPECT_EQ(packages_vector[1].get_nevra().get_name(), "package2");
}

TEST(ApiManifestTest, SetRepositories) {
    Manifest manifest;

    Repositories repositories;
    Repository repository1;
    repository1.set_id("fedora");
    Repository repository2;
    repository2.set_id("updates");
    repositories.add(repository1);
    repositories.add(repository2);

    manifest.set_repositories(repositories);

    EXPECT_EQ(manifest.get_repositories().size(), 2);

    auto repository1_copy = manifest.get_repositories().get("fedora");
    EXPECT_EQ(repository1_copy.get_id(), "fedora");

    auto repository2_copy = manifest.get_repositories().get("updates");
    EXPECT_EQ(repository2_copy.get_id(), "updates");
}

TEST(ApiManifestTest, CopyConstructorCreatesIndependentCopy) {
    Manifest manifest;
    manifest.set_document("my-manifest");

    Manifest copied_manifest(manifest);
    EXPECT_EQ(copied_manifest.get_document(), "my-manifest");
    copied_manifest.set_document("other-manifest");
    EXPECT_EQ(manifest.get_document(), "my-manifest");
}

TEST(ApiManifestTest, CopyAssignmentCreatesIndependentCopy) {
    Manifest manifest;
    manifest.set_document("my-manifest");

    Manifest copied_manifest;
    copied_manifest = manifest;
    EXPECT_EQ(copied_manifest.get_document(), "my-manifest");
    copied_manifest.set_document("other-manifest");
    EXPECT_EQ(manifest.get_document(), "my-manifest");
}

TEST(ApiManifestTest, MoveConstructorTransfersOwnership) {
    Manifest manifest;
    manifest.set_document("my-manifest");

    Manifest moved_manifest(std::move(manifest));
    EXPECT_EQ(moved_manifest.get_document(), "my-manifest");
}

TEST(ApiManifestTest, MoveAssignmentTransfersOwnership) {
    Manifest manifest;
    manifest.set_document("my-manifest");

    Manifest moved_manifest;
    moved_manifest = std::move(manifest);
    EXPECT_EQ(moved_manifest.get_document(), "my-manifest");
}

}