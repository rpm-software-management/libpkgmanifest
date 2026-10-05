// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/common/mocks/yaml/yamlnodefactorymock.hpp"
#include "impl/common/mocks/yaml/yamlnodeinternalmock.hpp"
#include "impl/common/mocks/yaml/yamlnodeinternalstub.hpp"
#include "impl/input/mocks/objects/modules/modulesmock.hpp"
#include "impl/input/objects/modules/modulesserializer.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal::input;

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::ReturnPointee;
using ::testing::Test;

class ModulesSerializerTest : public Test {
protected:
    virtual void SetUp() {
        auto node = std::make_unique<NiceMock<YamlNodeInternalMock>>();
        node_ptr = node.get();
        EXPECT_CALL(*node_ptr, insert(_, _)).Times(AnyNumber());

        auto node_factory = std::make_shared<NiceMock<YamlNodeFactoryMock>>();
        EXPECT_CALL(*node_factory, create()).WillOnce(Return(std::move(node))).WillRepeatedly([]() {
            return std::make_unique<YamlNodeInternalStub>();
        });

        serializer = std::make_unique<ModulesSerializer>(node_factory);
    }

    NiceMock<ModulesMock> modules;
    NiceMock<YamlNodeInternalMock> * node_ptr;
    std::unique_ptr<ModulesSerializer> serializer;
};

TEST_F(ModulesSerializerTest, SerializerSetsEnableListToYamlNode) {
    std::vector<std::string> enables = {"mod1:stream1", "mod2:stream2"};
    std::vector<std::string> disables;
    EXPECT_CALL(Const(modules), get_enables()).WillRepeatedly(ReturnPointee(&enables));
    EXPECT_CALL(Const(modules), get_disables()).WillRepeatedly(ReturnPointee(&disables));

    EXPECT_CALL(*node_ptr, insert("enable", _)).WillOnce([](const std::string &, std::unique_ptr<IYamlNode> node) {
        auto const & node_list = node->as_list();
        EXPECT_EQ(2, node_list.size());
        EXPECT_EQ("mod1:stream1", node_list[0]->as_string());
        EXPECT_EQ("mod2:stream2", node_list[1]->as_string());
    });

    serializer->serialize(modules);
}

TEST_F(ModulesSerializerTest, SerializerSetsDisableListToYamlNode) {
    std::vector<std::string> enables;
    std::vector<std::string> disables = {"mod3"};
    EXPECT_CALL(Const(modules), get_enables()).WillRepeatedly(ReturnPointee(&enables));
    EXPECT_CALL(Const(modules), get_disables()).WillRepeatedly(ReturnPointee(&disables));

    EXPECT_CALL(*node_ptr, insert("disable", _)).WillOnce([](const std::string &, std::unique_ptr<IYamlNode> node) {
        auto const & node_list = node->as_list();
        EXPECT_EQ(1, node_list.size());
        EXPECT_EQ("mod3", node_list[0]->as_string());
    });

    serializer->serialize(modules);
}

TEST(ModulesSerializerNullptrTest, SerializerReturnsNullptrWhenEmpty) {
    NiceMock<ModulesMock> modules;
    std::vector<std::string> empty;
    EXPECT_CALL(Const(modules), get_enables()).WillRepeatedly(ReturnPointee(&empty));
    EXPECT_CALL(Const(modules), get_disables()).WillRepeatedly(ReturnPointee(&empty));

    auto node_factory = std::make_shared<NiceMock<YamlNodeFactoryMock>>();
    auto serializer = std::make_unique<ModulesSerializer>(node_factory);
    auto serialized_node = serializer->serialize(modules);
    EXPECT_EQ(serialized_node, nullptr);
}

TEST_F(ModulesSerializerTest, SerializerReturnsNodeWhenEnablesNotEmpty) {
    std::vector<std::string> enables = {"mod1:stream1"};
    std::vector<std::string> disables;
    EXPECT_CALL(Const(modules), get_enables()).WillRepeatedly(ReturnPointee(&enables));
    EXPECT_CALL(Const(modules), get_disables()).WillRepeatedly(ReturnPointee(&disables));

    auto serialized_node = serializer->serialize(modules);
    EXPECT_EQ(serialized_node.get(), node_ptr);
}

}  // namespace
