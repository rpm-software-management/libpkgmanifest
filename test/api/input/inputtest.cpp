// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "libpkgmanifest/input/input.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::input;

TEST(ApiInputTest, DocumentIsCanonical) {
    Input input;
    EXPECT_EQ(input.get_document(), INPUT_DOCUMENT_IDENTIFIER);
}

TEST(ApiInputTest, VersionIsCanonical) {
    Input input;
    EXPECT_EQ(input.get_version().get_major(), CURRENT_INPUT_SCHEMA_VERSION.get_major());
    EXPECT_EQ(input.get_version().get_minor(), CURRENT_INPUT_SCHEMA_VERSION.get_minor());
    EXPECT_EQ(input.get_version().get_patch(), CURRENT_INPUT_SCHEMA_VERSION.get_patch());
}

TEST(ApiInputTest, SetRepositories) {
    Input input;

    Repositories repositories;
    Repository repository1;
    repository1.set_id("main");
    repository1.set_metalink("https://community.server.org/metalink");

    Repository repository2;
    repository2.set_id("sources");
    repository2.set_baseurl("https://src.location.lol/content/public/dist/lol2/source/SRPMS");

    repositories.add(repository1);
    repositories.add(repository2);

    input.set_repositories(repositories);

    auto & input_repositories = input.get_repositories();
    EXPECT_EQ(input_repositories.size(), 2);

    auto repository1_copy = input_repositories.get("main");
    EXPECT_EQ(repository1_copy.get_id(), "main");
    EXPECT_EQ(repository1_copy.get_metalink(), "https://community.server.org/metalink");

    auto repository2_copy = input_repositories.get("sources");
    EXPECT_EQ(repository2_copy.get_id(), "sources");
    EXPECT_EQ(repository2_copy.get_baseurl(), "https://src.location.lol/content/public/dist/lol2/source/SRPMS");
}

TEST(ApiInputTest, SetPackages) {
    Input input;

    Packages packages;
    packages.get_installs().push_back("bootc");
    packages.get_installs().push_back("dnf");
    packages.get_installs().push_back("podman");

    input.set_packages(packages);

    auto & input_packages = input.get_packages();
    EXPECT_EQ(input_packages.get_installs().size(), 3);
    EXPECT_THAT(input_packages.get_installs(), ::testing::ElementsAre("bootc", "dnf", "podman"));
}

TEST(ApiInputTest, SetModules) {
    Input input;

    Modules modules;
    modules.get_enables().push_back("module1");
    modules.get_enables().push_back("module2");

    input.set_modules(modules);

    auto & input_modules = input.get_modules();
    EXPECT_EQ(input_modules.get_enables().size(), 2);
    EXPECT_THAT(input_modules.get_enables(), ::testing::ElementsAre("module1", "module2"));
}

TEST(ApiInputTest, SetOptions) {
    Input input;

    Options options;
    options.set_allow_erasing(true);

    input.set_options(options);

    auto & input_options = input.get_options();
    EXPECT_EQ(input_options.get_allow_erasing(), true);
}

TEST(ApiInputTest, CopyConstructorCreatesIndependentCopy) {
    Input input;
    input.get_archs().push_back("x86_64");

    Input copied_input(input);
    copied_input.get_archs().push_back("aarch64");
    EXPECT_THAT(input.get_archs(), ::testing::ElementsAre("x86_64"));
    EXPECT_THAT(copied_input.get_archs(), ::testing::ElementsAre("x86_64", "aarch64"));
}

TEST(ApiInputTest, CopyAssignmentCreatesIndependentCopy) {
    Input input;
    input.get_archs().push_back("x86_64");

    Input copied_input;
    copied_input = input;
    copied_input.get_archs().push_back("aarch64");
    EXPECT_THAT(input.get_archs(), ::testing::ElementsAre("x86_64"));
    EXPECT_THAT(copied_input.get_archs(), ::testing::ElementsAre("x86_64", "aarch64"));
}

TEST(ApiInputTest, MoveConstructorTransfersOwnership) {
    Input input;
    input.get_archs().push_back("x86_64");

    Input moved_input(std::move(input));
    EXPECT_THAT(moved_input.get_archs(), ::testing::ElementsAre("x86_64"));
}

TEST(ApiInputTest, MoveAssignmentTransfersOwnership) {
    Input input;
    input.get_archs().push_back("x86_64");

    Input moved_input;
    moved_input = std::move(input);
    EXPECT_THAT(moved_input.get_archs(), ::testing::ElementsAre("x86_64"));
}

}  // namespace
