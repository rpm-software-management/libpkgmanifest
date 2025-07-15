// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "libpkgmanifest/manifest/package.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::manifest;

TEST(ApiPackageTest, SetRepoId) {
    Package package;
    package.set_repo_id("main");
    EXPECT_EQ(package.get_repo_id(), "main");
}

TEST(ApiPackageTest, SetLocation) {
    Package package;
    package.set_location("path/to/package");
    EXPECT_EQ(package.get_location(), "path/to/package");
}

TEST(ApiPackageTest, SetSize) {
    Package package;
    package.set_size(1024);
    EXPECT_EQ(package.get_size(), 1024);
}

TEST(ApiPackageTest, SetChecksum) {
    Package package;

    Checksum checksum;
    checksum.set_method(ChecksumMethod::SHA256);
    checksum.set_digest("1234567890abcdef");

    package.set_checksum(checksum);

    auto & package_checksum = package.get_checksum();
    EXPECT_EQ(package_checksum.get_method(), ChecksumMethod::SHA256);
    EXPECT_EQ(package_checksum.get_digest(), "1234567890abcdef");
}

TEST(ApiPackageTest, SetNevra) {
    Package package;
    
    Nevra nevra;
    nevra.set_name("package1");

    package.set_nevra(nevra);

    auto & package_nevra = package.get_nevra();
    EXPECT_EQ(package_nevra.get_name(), "package1");
}

TEST(ApiPackageTest, SetSrpm) {
    Package package;
    
    Nevra srpm;
    srpm.set_name("source1");

    package.set_srpm(srpm);

    auto & package_srpm = package.get_srpm();
    EXPECT_EQ(package_srpm.get_name(), "source1");
}

TEST(ApiPackageTest, SetModule) {
    Package package;

    Module module;
    module.set_name("module1");

    package.set_module(module);

    auto & package_module = package.get_module();
    EXPECT_EQ(package_module.get_name(), "module1");
}

TEST(ApiPackageTest, SetRepository) {
    Package package;

    Repository repository;
    repository.set_id("main");

    Repositories repositories;
    repositories.add(repository);

    package.set_repo_id("main");
    package.attach(repositories);

    auto & package_repository = package.get_repository();
    EXPECT_EQ(package_repository.get_id(), "main");
}

TEST(ApiPackageTest, CopyConstructorCreatesIndependentCopy) {
    Package package;
    package.set_location("path/to/package");

    Package copied_package(package);
    EXPECT_EQ(copied_package.get_location(), "path/to/package");
    copied_package.set_location("path/to/other/package");
    EXPECT_EQ(package.get_location(), "path/to/package");
}

TEST(ApiPackageTest, CopyAssignmentCreatesIndependentCopy) {
    Package package;
    package.set_location("path/to/package");

    Package copied_package;
    copied_package = package;
    EXPECT_EQ(copied_package.get_location(), "path/to/package");
    copied_package.set_location("path/to/other/package");
    EXPECT_EQ(package.get_location(), "path/to/package");
}

TEST(ApiPackageTest, MoveConstructorTransfersOwnership) {
    Package package;
    package.set_location("path/to/package");

    Package moved_package(std::move(package));
    EXPECT_EQ(moved_package.get_location(), "path/to/package");
}

TEST(ApiPackageTest, MoveAssignmentTransfersOwnership) {
    Package package;
    package.set_location("path/to/package");

    Package moved_package;
    moved_package = std::move(package);
    EXPECT_EQ(moved_package.get_location(), "path/to/package");
}

}