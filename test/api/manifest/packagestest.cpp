#include "libpkgmanifest/manifest/packages.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::manifest;

TEST(ApiManifestPackagesTest, ContainsPackage) {
    Packages packages;

    Package package;
    package.get_nevra().set_name("pkg1");

    packages.add(package);
    EXPECT_EQ(packages.contains(package), true);
}

TEST(ApiManifestPackagesTest, GetPackages) {
    Packages packages;

    Package package1;
    package1.get_nevra().set_name("pkg1");
    Package package2;
    package2.get_nevra().set_name("pkg2");

    packages.add(package1);
    packages.add(package2);

    auto packages_vector = packages.get();
    EXPECT_EQ(packages_vector.size(), 2);
    EXPECT_EQ(packages_vector[0].get_nevra().get_name(), "pkg1");
    EXPECT_EQ(packages_vector[1].get_nevra().get_name(), "pkg2");
}

TEST(ApiManifestPackagesTest, GetBasearchPackages) {
    Packages packages;

    Package package1;
    package1.get_nevra().set_name("pkg1");
    package1.get_nevra().set_arch("x86_64");
    Package package2;
    package2.get_nevra().set_name("pkg2");
    package2.get_nevra().set_arch("aarch64");

    packages.add(package1);
    packages.add(package2);

    auto packages_vector = packages.get("x86_64");
    EXPECT_EQ(packages_vector.size(), 1);
    EXPECT_EQ(packages_vector[0].get_nevra().get_name(), "pkg1");
    
    packages_vector = packages.get("aarch64");
    EXPECT_EQ(packages_vector.size(), 1);
    EXPECT_EQ(packages_vector[0].get_nevra().get_name(), "pkg2");
}

TEST(ApiManifestPackagesTest, GetBasearchPackagesWithParentArchs) {
    Packages packages;

    Package package1;
    package1.get_nevra().set_name("pkg1");
    package1.get_nevra().set_arch("x86_64");
    Package package2;
    package2.get_nevra().set_name("pkg2");
    package2.get_nevra().set_arch("aarch64");
    Package package3;
    package3.get_nevra().set_name("pkg3");
    package3.get_nevra().set_arch("noarch");
    Package package4;
    package4.get_nevra().set_name("pkg4");
    package4.get_nevra().set_arch("src");

    packages.add(package1, "x86_64");
    packages.add(package2, "aarch64");
    packages.add(package3, "x86_64");
    packages.add(package4, "x86_64");

    // Get everything linked to x86_64 (without sources)
    auto packages_vector = packages.get("x86_64");
    EXPECT_EQ(packages_vector.size(), 2);
    EXPECT_EQ(packages_vector[0].get_nevra().get_name(), "pkg1");
    EXPECT_EQ(packages_vector[1].get_nevra().get_name(), "pkg3");

    // Get everything linked to x86_64 (with sources)
    packages_vector = packages.get("x86_64", true);
    EXPECT_EQ(packages_vector.size(), 3);
    EXPECT_EQ(packages_vector[0].get_nevra().get_name(), "pkg1");
    EXPECT_EQ(packages_vector[1].get_nevra().get_name(), "pkg3");
    EXPECT_EQ(packages_vector[2].get_nevra().get_name(), "pkg4");
}

TEST(ApiManifestPackagesTest, AttachRepositories) {
    Package package;
    package.get_nevra().set_name("pkg1");
    package.get_nevra().set_arch("x86_64");
    package.set_repo_id("main");

    Repository repository;
    repository.set_id("main");

    Repositories repositories;
    repositories.add(repository);

    Packages packages;
    packages.add(package);
    packages.attach(repositories);

    auto packages_vector = packages.get();
    auto get_package = packages_vector[0];
    
    EXPECT_EQ(get_package.get_repository().get_id(), "main");
}

TEST(ApiManifestPackagesTest, CopyConstructorCreatesIndependentCopy) {
    Packages packages;

    Package package1;
    package1.get_nevra().set_name("pkg1");
    Package package2;
    package2.get_nevra().set_name("pkg2");

    packages.add(package1);

    Packages copied_packages(packages);
    EXPECT_EQ(copied_packages.contains(package1), true);
    EXPECT_EQ(copied_packages.get()[0].get_nevra().get_name(), "pkg1");

    copied_packages.add(package2);
    EXPECT_EQ(packages.contains(package2), false);
}

TEST(ApiManifestPackagesTest, CopyAssignmentCreatesIndependentCopy) {
    Packages packages;

    Package package1;
    package1.get_nevra().set_name("pkg1");
    Package package2;
    package2.get_nevra().set_name("pkg2");

    packages.add(package1);

    Packages copied_packages;
    copied_packages = packages;
    EXPECT_EQ(copied_packages.contains(package1), true);
    EXPECT_EQ(copied_packages.get()[0].get_nevra().get_name(), "pkg1");

    copied_packages.add(package2);
    EXPECT_EQ(packages.contains(package2), false);
}

TEST(ApiManifestPackagesTest, MoveConstructorTransfersOwnership) {
    Packages packages;

    Package package1;
    package1.get_nevra().set_name("pkg1");
    Package package2;
    package2.get_nevra().set_name("pkg2");

    packages.add(package1);

    Packages moved_packages(std::move(packages));
    EXPECT_EQ(moved_packages.contains(package1), true);
    EXPECT_EQ(moved_packages.get()[0].get_nevra().get_name(), "pkg1");
}

TEST(ApiManifestPackagesTest, MoveAssignmentTransfersOwnership) {
    Packages packages;

    Package package1;
    package1.get_nevra().set_name("pkg1");
    Package package2;
    package2.get_nevra().set_name("pkg2");

    packages.add(package1);

    Packages moved_packages;
    moved_packages = std::move(packages);
    EXPECT_EQ(moved_packages.contains(package1), true);
    EXPECT_EQ(moved_packages.get()[0].get_nevra().get_name(), "pkg1");
}

}