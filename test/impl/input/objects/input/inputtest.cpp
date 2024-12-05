#include "impl/common/mocks/objects/repositories/repositoriesmock.hpp"
#include "impl/common/mocks/objects/version/versionmock.hpp"

#include "impl/input/objects/input/input.hpp"

#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal::input;

using ::testing::NiceMock;
using ::testing::Return;

TEST(InputTest, DefaultDocumentIsEmpty) {
    EXPECT_EQ(std::string(), Input().get_document());
}

TEST(InputTest, DefaultVersionIsNull) {
    EXPECT_EQ(nullptr, &Input().get_version());
}

TEST(InputTest, DefaultRepositoriesIsNull) {
    EXPECT_EQ(nullptr, &Input().get_repositories());
}

TEST(InputTest, DefaultPackagesIsEmpty) {
    EXPECT_TRUE(Input().get_packages().empty());
}

TEST(InputTest, DefaultModulesIsEmpty) {
    EXPECT_TRUE(Input().get_modules().empty());
}

TEST(InputTest, DefaultArchsIsEmpty) {
    EXPECT_TRUE(Input().get_archs().empty());
}

TEST(InputTest, DefaultAllowErasingIsFalse) {
    EXPECT_FALSE(Input().get_allow_erasing());
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

TEST(InputTest, SetAllowErasingIsReturned) {
    Input input;
    input.set_allow_erasing(true);
    EXPECT_TRUE(input.get_allow_erasing());
}

TEST(InputTest, ClonedObjectHasSameValuesAsOriginal) {
    // TODO: Tests cloned complex objects are the same

    auto repositories = std::make_unique<NiceMock<RepositoriesMock>>();
    auto cloned_repositories = std::make_unique<NiceMock<RepositoriesMock>>();
    auto version = std::make_unique<NiceMock<VersionMock>>();
    auto cloned_version = std::make_unique<NiceMock<VersionMock>>();
    EXPECT_CALL(*version, get_major()).WillOnce(Return(4));
    EXPECT_CALL(*cloned_version, get_major()).WillOnce(Return(4));
    EXPECT_CALL(*version, clone()).WillOnce(Return(std::move(cloned_version)));

    Input input;
    input.set_document("input1");
    input.set_version(std::move(version));
    input.set_repositories(std::move(repositories));
    input.set_allow_erasing(true);

    auto clone(input.clone());
    EXPECT_EQ(input.get_document(), clone->get_document());
    EXPECT_EQ(input.get_version().get_major(), clone->get_version().get_major());
    EXPECT_EQ(input.get_allow_erasing(), clone->get_allow_erasing());
}

}