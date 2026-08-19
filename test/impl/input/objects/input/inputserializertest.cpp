// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/common/mocks/objects/repositories/repositoriesmock.hpp"
#include "impl/common/mocks/objects/repositories/repositoriesserializermock.hpp"
#include "impl/common/mocks/objects/version/versionmock.hpp"
#include "impl/common/mocks/objects/version/versionserializermock.hpp"
#include "impl/common/mocks/yaml/yamlnodefactorymock.hpp"
#include "impl/common/mocks/yaml/yamlnodeinternalmock.hpp"
#include "impl/common/mocks/yaml/yamlnodeinternalstub.hpp"
#include "impl/input/mocks/objects/input/inputmock.hpp"
#include "impl/input/mocks/objects/modules/modulesmock.hpp"
#include "impl/input/mocks/objects/modules/modulesserializermock.hpp"
#include "impl/input/mocks/objects/options/optionsmock.hpp"
#include "impl/input/mocks/objects/options/optionsserializermock.hpp"
#include "impl/input/mocks/objects/packages/packagesmock.hpp"
#include "impl/input/mocks/objects/packages/packagesserializermock.hpp"
#include "impl/input/objects/input/inputserializer.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal::input;

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::Matcher;
using ::testing::NiceMock;
using ::testing::Pointer;
using ::testing::Ref;
using ::testing::Return;
using ::testing::ReturnPointee;
using ::testing::Test;

class InputSerializerTest : public Test {
protected:
    virtual void SetUp() {
        auto packages_serializer = std::make_unique<NiceMock<PackagesSerializerMock>>();
        packages_serializer_ptr = packages_serializer.get();

        auto repositories_serializer = std::make_unique<NiceMock<RepositoriesSerializerMock>>();
        repositories_serializer_ptr = repositories_serializer.get();

        auto version_serializer = std::make_unique<NiceMock<VersionSerializerMock>>();
        version_serializer_ptr = version_serializer.get();

        auto modules_serializer = std::make_unique<NiceMock<ModulesSerializerMock>>();
        modules_serializer_ptr = modules_serializer.get();

        auto options_serializer = std::make_unique<NiceMock<OptionsSerializerMock>>();
        options_serializer_ptr = options_serializer.get();

        auto node = std::make_unique<NiceMock<YamlNodeInternalMock>>();
        node_ptr = node.get();
        EXPECT_CALL(*node_ptr, insert(_, _)).Times(AnyNumber());

        auto node_factory = std::make_shared<NiceMock<YamlNodeFactoryMock>>();
        EXPECT_CALL(*node_factory, create()).WillOnce(Return(std::move(node))).WillRepeatedly([]() {
            return std::make_unique<YamlNodeInternalStub>();
        });

        EXPECT_CALL(Const(input), get_packages()).WillRepeatedly(ReturnPointee(&packages));
        EXPECT_CALL(Const(input), get_repositories()).WillRepeatedly(ReturnPointee(&repositories));
        EXPECT_CALL(Const(input), get_version()).WillRepeatedly(ReturnPointee(&version));
        EXPECT_CALL(Const(input), get_modules()).WillRepeatedly(ReturnPointee(&modules));
        EXPECT_CALL(Const(input), get_options()).WillRepeatedly(ReturnPointee(&options));
        EXPECT_CALL(Const(input), get_archs()).WillRepeatedly(ReturnPointee(&archs));

        serializer = std::make_unique<InputSerializer>(
            node_factory,
            std::move(packages_serializer),
            std::move(repositories_serializer),
            std::move(version_serializer),
            std::move(modules_serializer),
            std::move(options_serializer));
    }

    NiceMock<InputMock> input;
    NiceMock<PackagesMock> packages;
    NiceMock<RepositoriesMock> repositories;
    NiceMock<VersionMock> version;
    NiceMock<ModulesMock> modules;
    NiceMock<OptionsMock> options;
    std::vector<std::string> archs;
    NiceMock<YamlNodeInternalMock> * node_ptr;
    NiceMock<PackagesSerializerMock> * packages_serializer_ptr;
    NiceMock<RepositoriesSerializerMock> * repositories_serializer_ptr;
    NiceMock<VersionSerializerMock> * version_serializer_ptr;
    NiceMock<ModulesSerializerMock> * modules_serializer_ptr;
    NiceMock<OptionsSerializerMock> * options_serializer_ptr;
    std::unique_ptr<InputSerializer> serializer;
};

TEST_F(InputSerializerTest, SerializerSetsDocumentAsStringToYamlNode) {
    EXPECT_CALL(input, get_document()).WillOnce(Return("rpm-package-input"));

    EXPECT_CALL(*node_ptr, insert("document", _)).WillOnce([](const std::string &, std::unique_ptr<IYamlNode> node) {
        EXPECT_EQ("rpm-package-input", node->as_string());
    });

    serializer->serialize(input);
}

TEST_F(InputSerializerTest, SerializerSetsVersionFromVersionSerializer) {
    auto version_node = std::make_unique<NiceMock<YamlNodeInternalStub>>();
    auto version_node_ptr = version_node.get();
    EXPECT_CALL(*version_serializer_ptr, serialize(Ref(version))).WillOnce(Return(std::move(version_node)));

    EXPECT_CALL(*node_ptr, insert("version", Pointer(version_node_ptr)));

    serializer->serialize(input);
}

TEST_F(InputSerializerTest, SerializerSetsRepositoriesFromRepositoriesSerializer) {
    auto repositories_node = std::make_unique<NiceMock<YamlNodeInternalStub>>();
    auto repositories_node_ptr = repositories_node.get();

    EXPECT_CALL(*repositories_serializer_ptr, serialize(Ref(repositories)))
        .WillOnce(Return(std::move(repositories_node)));

    EXPECT_CALL(*node_ptr, insert("repositories", Pointer(repositories_node_ptr)));

    serializer->serialize(input);
}

TEST_F(InputSerializerTest, SerializerSetsPackagesFromPackagesSerializer) {
    auto packages_node = std::make_unique<NiceMock<YamlNodeInternalStub>>();
    auto packages_node_ptr = packages_node.get();

    EXPECT_CALL(*packages_serializer_ptr, serialize(Ref(packages))).WillOnce(Return(std::move(packages_node)));

    EXPECT_CALL(*node_ptr, insert("packages", Pointer(packages_node_ptr)));

    serializer->serialize(input);
}

TEST_F(InputSerializerTest, SerializerSetsModulesWhenSerializerReturnsNode) {
    auto modules_node = std::make_unique<NiceMock<YamlNodeInternalStub>>();
    auto modules_node_ptr = modules_node.get();

    EXPECT_CALL(*modules_serializer_ptr, serialize(Ref(modules))).WillOnce(Return(std::move(modules_node)));

    EXPECT_CALL(*node_ptr, insert("modules", Pointer(modules_node_ptr)));

    serializer->serialize(input);
}

TEST_F(InputSerializerTest, SerializerDoesNotSetModulesWhenSerializerReturnsNullptr) {
    EXPECT_CALL(*modules_serializer_ptr, serialize(Ref(modules))).WillOnce(Return(nullptr));

    EXPECT_CALL(*node_ptr, insert("modules", _)).Times(0);

    serializer->serialize(input);
}

TEST_F(InputSerializerTest, SerializerSetsArchsAsListToYamlNode) {
    archs = {"i686", "x86_64", "aarch64"};

    EXPECT_CALL(*node_ptr, insert("archs", _)).WillOnce([](const std::string &, std::unique_ptr<IYamlNode> node) {
        auto const & node_list = node->as_list();
        EXPECT_EQ(3, node_list.size());
        EXPECT_EQ("i686", node_list[0]->as_string());
        EXPECT_EQ("x86_64", node_list[1]->as_string());
        EXPECT_EQ("aarch64", node_list[2]->as_string());
    });

    serializer->serialize(input);
}

TEST_F(InputSerializerTest, SerializerSetsOptionsWhenSerializerReturnsNode) {
    auto options_node = std::make_unique<NiceMock<YamlNodeInternalStub>>();
    auto options_node_ptr = options_node.get();

    EXPECT_CALL(*options_serializer_ptr, serialize(Ref(options))).WillOnce(Return(std::move(options_node)));

    EXPECT_CALL(*node_ptr, insert("options", Pointer(options_node_ptr)));

    serializer->serialize(input);
}

TEST_F(InputSerializerTest, SerializerDoesNotSetOptionsWhenSerializerReturnsNullptr) {
    EXPECT_CALL(*options_serializer_ptr, serialize(Ref(options))).WillOnce(Return(nullptr));

    EXPECT_CALL(*node_ptr, insert("options", _)).Times(0);

    serializer->serialize(input);
}

TEST_F(InputSerializerTest, SerializerReturnsTheObjectCreatedByFactory) {
    auto serialized_node = serializer->serialize(input);
    EXPECT_EQ(serialized_node.get(), node_ptr);
}

}  // namespace
