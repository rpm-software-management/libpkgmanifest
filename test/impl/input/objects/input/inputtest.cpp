// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/common/mocks/objects/repositories/repositoriesmock.hpp"
#include "impl/input/mocks/objects/modules/modulesmock.hpp"
#include "impl/input/mocks/objects/options/optionsmock.hpp"
#include "impl/input/mocks/objects/packages/packagesmock.hpp"
#include "impl/input/objects/input/input.hpp"
#include "impl/input/objects/input/inputfactory.hpp"

#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal::input;

using ::testing::NiceMock;
using ::testing::Return;

Input create_input() {
    return Input();
}

TEST(InputTest, DefaultArchsIsEmpty) {
    auto input = create_input();
    EXPECT_TRUE(input.get_archs().empty());
    EXPECT_TRUE(static_cast<const Input &>(input).get_archs().empty());
}

TEST(InputTest, ConstantMetadataIsReturned) {
    Input input;
    EXPECT_EQ(INPUT_DOCUMENT_ID, input.get_document());
    EXPECT_EQ(INPUT_DOCUMENT_VERSION.get_major(), input.get_version().get_major());
    EXPECT_EQ(INPUT_DOCUMENT_VERSION.get_minor(), input.get_version().get_minor());
    EXPECT_EQ(INPUT_DOCUMENT_VERSION.get_patch(), input.get_version().get_patch());
}

TEST(InputTest, SetRepositoriesObjectIsReturned) {
    auto repositories = std::make_unique<NiceMock<RepositoriesMock>>();
    auto repositories_ptr = repositories.get();

    auto input = create_input();
    input.set_repositories(std::move(repositories));

    EXPECT_EQ(repositories_ptr, &input.get_repositories());

    const auto & const_input = input;
    EXPECT_EQ(repositories_ptr, &const_input.get_repositories());
}

TEST(InputTest, SetPackagesObjectIsReturned) {
    auto packages = std::make_unique<NiceMock<PackagesMock>>();
    auto packages_ptr = packages.get();

    auto input = create_input();
    input.set_packages(std::move(packages));

    EXPECT_EQ(packages_ptr, &input.get_packages());

    const auto & const_input = input;
    EXPECT_EQ(packages_ptr, &const_input.get_packages());
}

TEST(InputTest, SetModulesObjectIsReturned) {
    auto modules = std::make_unique<NiceMock<ModulesMock>>();
    auto modules_ptr = modules.get();

    auto input = create_input();
    input.set_modules(std::move(modules));

    EXPECT_EQ(modules_ptr, &input.get_modules());

    const auto & const_input = input;
    EXPECT_EQ(modules_ptr, &const_input.get_modules());
}

TEST(InputTest, SetOptionsObjectIsReturned) {
    auto options = std::make_unique<NiceMock<OptionsMock>>();
    auto options_ptr = options.get();

    auto input = create_input();
    input.set_options(std::move(options));

    EXPECT_EQ(options_ptr, &input.get_options());

    const auto & const_input = input;
    EXPECT_EQ(options_ptr, &const_input.get_options());
}

TEST(InputTest, ClonedObjectHasSameValuesAsOriginal) {
    // TODO(jkolarik): Tests cloned complex objects are the same

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
    input.set_repositories(std::move(repositories));
    input.set_packages(std::move(packages));
    input.set_modules(std::move(modules));
    input.set_options(std::move(options));

    auto clone(input.clone());
    EXPECT_EQ(input.get_document(), clone->get_document());
    EXPECT_EQ(input.get_version().get_major(), clone->get_version().get_major());
}

}  // namespace
