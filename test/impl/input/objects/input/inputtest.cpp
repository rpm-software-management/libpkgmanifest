// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/common/mocks/objects/repositories/repositoriesmock.hpp"
#include "impl/common/mocks/objects/version/versionmock.hpp"
#include "impl/input/mocks/objects/modules/modulesmock.hpp"
#include "impl/input/mocks/objects/options/optionsmock.hpp"
#include "impl/input/mocks/objects/packages/packagesmock.hpp"

#include "impl/input/objects/input/input.hpp"

#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal::input;

using ::testing::NiceMock;
using ::testing::Return;

TEST(InputTest, DefaultDocumentIsEmpty) {
    EXPECT_EQ(std::string(), Input().get_document());
}

TEST(InputTest, DefaultArchsIsEmpty) {
    EXPECT_TRUE(Input().get_archs().empty());
    EXPECT_TRUE(static_cast<const Input &>(Input()).get_archs().empty());
}

TEST(InputTest, SetDocumentIsReturned) {
    Input input;
    input.set_document("document");
    EXPECT_EQ("document", input.get_document());
}

TEST(InputTest, SetVersionObjectIsReturned) {
    auto version = std::make_unique<NiceMock<VersionMock>>();
    auto version_ptr = version.get();

    Input input;
    input.set_version(std::move(version));

    EXPECT_EQ(version_ptr, &input.get_version());

    const auto & const_input = input;
    EXPECT_EQ(version_ptr, &const_input.get_version());
}

TEST(InputTest, SetRepositoriesObjectIsReturned) {
    auto repositories = std::make_unique<NiceMock<RepositoriesMock>>();
    auto repositories_ptr = repositories.get();

    Input input;
    input.set_repositories(std::move(repositories));

    EXPECT_EQ(repositories_ptr, &input.get_repositories());

    const auto & const_input = input;
    EXPECT_EQ(repositories_ptr, &const_input.get_repositories());
}

TEST(InputTest, SetPackagesObjectIsReturned) {
    auto packages = std::make_unique<NiceMock<PackagesMock>>();
    auto packages_ptr = packages.get();

    Input input;
    input.set_packages(std::move(packages));

    EXPECT_EQ(packages_ptr, &input.get_packages());

    const auto & const_input = input;
    EXPECT_EQ(packages_ptr, &const_input.get_packages());
}

TEST(InputTest, SetModulesObjectIsReturned) {
    auto modules = std::make_unique<NiceMock<ModulesMock>>();
    auto modules_ptr = modules.get();

    Input input;
    input.set_modules(std::move(modules));

    EXPECT_EQ(modules_ptr, &input.get_modules());

    const auto & const_input = input;
    EXPECT_EQ(modules_ptr, &const_input.get_modules());
}

TEST(InputTest, SetOptionsObjectIsReturned) {
    auto options = std::make_unique<NiceMock<OptionsMock>>();
    auto options_ptr = options.get();

    Input input;
    input.set_options(std::move(options));

    EXPECT_EQ(options_ptr, &input.get_options());

    const auto & const_input = input;
    EXPECT_EQ(options_ptr, &const_input.get_options());
}

TEST(InputTest, ClonedObjectHasSameValuesAsOriginal) {
    // TODO(jkolarik): Tests cloned complex objects are the same

    auto version = std::make_unique<NiceMock<VersionMock>>();
    auto cloned_version = std::make_unique<NiceMock<VersionMock>>();
    EXPECT_CALL(*version, get_major()).WillOnce(Return(4));
    EXPECT_CALL(*cloned_version, get_major()).WillOnce(Return(4));
    EXPECT_CALL(*version, clone()).WillOnce(Return(std::move(cloned_version)));

    auto repositories = std::make_unique<NiceMock<RepositoriesMock>>();
    auto cloned_repositories = std::make_unique<NiceMock<RepositoriesMock>>();
    EXPECT_CALL(*repositories, clone()).WillOnce(Return(std::move(cloned_repositories)));

    auto packages = std::make_unique<NiceMock<PackagesMock>>();
    auto cloned_packages = std::make_unique<NiceMock<PackagesMock>>();
    EXPECT_CALL(*packages, clone()).WillOnce(Return(std::move(cloned_packages)));

    auto modules = std::make_unique<NiceMock<ModulesMock>>();
    auto cloned_modules = std::make_unique<NiceMock<ModulesMock>>();
    EXPECT_CALL(*modules, clone()).WillOnce(Return(std::move(cloned_modules)));

    auto options = std::make_unique<NiceMock<OptionsMock>>();
    auto cloned_options = std::make_unique<NiceMock<OptionsMock>>();
    EXPECT_CALL(*options, clone()).WillOnce(Return(std::move(cloned_options)));

    Input input;
    input.set_document("input1");
    input.set_version(std::move(version));
    input.set_repositories(std::move(repositories));
    input.set_packages(std::move(packages));
    input.set_modules(std::move(modules));
    input.set_options(std::move(options));

    auto clone(input.clone());
    EXPECT_EQ(input.get_document(), clone->get_document());
    EXPECT_EQ(input.get_version().get_major(), clone->get_version().get_major());
}

}