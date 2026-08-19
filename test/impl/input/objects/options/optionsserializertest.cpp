// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/common/mocks/yaml/yamlnodefactorymock.hpp"
#include "impl/common/mocks/yaml/yamlnodeinternalmock.hpp"
#include "impl/common/mocks/yaml/yamlnodeinternalstub.hpp"
#include "impl/input/mocks/objects/options/optionsmock.hpp"
#include "impl/input/objects/options/optionsserializer.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal::input;

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::Test;

class OptionsSerializerTest : public Test {
protected:
    virtual void SetUp() {
        auto node = std::make_unique<NiceMock<YamlNodeInternalMock>>();
        node_ptr = node.get();
        EXPECT_CALL(*node_ptr, insert(_, _)).Times(AnyNumber());

        auto node_factory = std::make_shared<NiceMock<YamlNodeFactoryMock>>();
        EXPECT_CALL(*node_factory, create()).WillOnce(Return(std::move(node))).WillRepeatedly([]() {
            return std::make_unique<YamlNodeInternalStub>();
        });

        serializer = std::make_unique<OptionsSerializer>(node_factory);
    }

    NiceMock<OptionsMock> options;
    NiceMock<YamlNodeInternalMock> * node_ptr;
    std::unique_ptr<OptionsSerializer> serializer;
};

TEST_F(OptionsSerializerTest, SerializerSetsAllowErasingWhenTrue) {
    EXPECT_CALL(options, has_allow_erasing()).WillOnce(Return(true));
    EXPECT_CALL(options, get_allow_erasing()).WillOnce(Return(true));

    EXPECT_CALL(*node_ptr, insert("allow_erasing", _))
        .WillOnce([](const std::string &, std::unique_ptr<IYamlNode> node) { EXPECT_EQ(true, node->as_bool()); });

    serializer->serialize(options);
}

TEST_F(OptionsSerializerTest, SerializerSetsAllowErasingWhenExplicitlyFalse) {
    EXPECT_CALL(options, has_allow_erasing()).WillOnce(Return(true));
    EXPECT_CALL(options, get_allow_erasing()).WillOnce(Return(false));

    EXPECT_CALL(*node_ptr, insert("allow_erasing", _))
        .WillOnce([](const std::string &, std::unique_ptr<IYamlNode> node) { EXPECT_EQ(false, node->as_bool()); });

    serializer->serialize(options);
}

TEST(OptionsSerializerNullptrTest, SerializerReturnsNullptrWhenNoOptionsSet) {
    NiceMock<OptionsMock> options;
    EXPECT_CALL(options, has_allow_erasing()).WillOnce(Return(false));

    auto node_factory = std::make_shared<NiceMock<YamlNodeFactoryMock>>();
    auto serializer = std::make_unique<OptionsSerializer>(node_factory);
    auto serialized_node = serializer->serialize(options);
    EXPECT_EQ(serialized_node, nullptr);
}

TEST_F(OptionsSerializerTest, SerializerReturnsNodeWhenOptionsSet) {
    EXPECT_CALL(options, has_allow_erasing()).WillOnce(Return(true));
    EXPECT_CALL(options, get_allow_erasing()).WillOnce(Return(true));

    auto serialized_node = serializer->serialize(options);
    EXPECT_EQ(serialized_node.get(), node_ptr);
}

}  // namespace
