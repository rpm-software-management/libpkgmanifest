#include "libpkgmanifest/mocks/objects/version/versionmock.hpp"
#include "libpkgmanifest/mocks/yaml/yamlnodefactorymock.hpp"
#include "libpkgmanifest/mocks/yaml/yamlnodeinternalmock.hpp"

#include "libpkgmanifest/objects/version/versionserializer.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal;

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::Test;

class VersionSerializerTest : public Test {
protected:
    virtual void SetUp() {
        auto node = std::make_unique<NiceMock<YamlNodeInternalMock>>();
        node_ptr = node.get();

        auto node_factory = std::make_shared<NiceMock<YamlNodeFactoryMock>>();
        EXPECT_CALL(*node_factory, create()).WillOnce(Return(std::move(node)));

        serializer = std::make_unique<VersionSerializer>(node_factory);
    }

    NiceMock<YamlNodeInternalMock> * node_ptr;
    std::unique_ptr<VersionSerializer> serializer;
};

TEST_F(VersionSerializerTest, SerializerSetsVersionAsStringToYamlNode) {
    NiceMock<VersionMock> version;
    EXPECT_CALL(version, get_major()).WillOnce(Return(3));
    EXPECT_CALL(version, get_minor()).WillOnce(Return(2));
    EXPECT_CALL(version, get_patch()).WillOnce(Return(1));
    EXPECT_CALL(*node_ptr, set("3.2.1"));
    serializer->serialize(version);
}

TEST_F(VersionSerializerTest, SerializerReturnsTheObjectCreatedByFactory) {
    NiceMock<VersionMock> version;
    auto serialized_node = serializer->serialize(version);
    EXPECT_EQ(serialized_node.get(), node_ptr);
}

}