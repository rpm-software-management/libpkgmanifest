#include "impl/manifest/mocks/objects/module/modulemock.hpp"
#include "impl/common/mocks/yaml/yamlnodefactorymock.hpp"
#include "impl/common/mocks/yaml/yamlnodeinternalmock.hpp"

#include "impl/manifest/objects/module/moduleserializer.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal::manifest;

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::Test;

class ModuleSerializerTest : public Test {
protected:
    virtual void SetUp() {
        auto node = std::make_unique<NiceMock<YamlNodeInternalMock>>();
        node_ptr = node.get();

        auto node_factory = std::make_shared<NiceMock<YamlNodeFactoryMock>>();
        EXPECT_CALL(*node_factory, create()).WillOnce(Return(std::move(node)));

        serializer = std::make_unique<ModuleSerializer>(node_factory);
    }

    NiceMock<YamlNodeInternalMock> * node_ptr;
    std::unique_ptr<ModuleSerializer> serializer;
};

TEST_F(ModuleSerializerTest, SerializerSetsNameAndStreamToYamlNode) {
    NiceMock<ModuleMock> module;
    EXPECT_CALL(module, get_name()).WillOnce(Return("harold"));
    EXPECT_CALL(module, get_stream()).WillOnce(Return("live"));
    EXPECT_CALL(*node_ptr, set(std::string("harold:live")));
    serializer->serialize(module);
}

TEST_F(ModuleSerializerTest, SerializerReturnsTheObjectCreatedByFactory) {
    NiceMock<ModuleMock> module;
    auto serialized_node = serializer->serialize(module);
    EXPECT_EQ(serialized_node.get(), node_ptr);
}

}