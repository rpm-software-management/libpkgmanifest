#include "liblockfile/mocks/objects/version/versionfactorymock.hpp"
#include "liblockfile/mocks/objects/version/versioninternalmock.hpp"
#include "liblockfile/mocks/yaml/yamlnodemock.hpp"

#include "liblockfile/objects/version/versionparser.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace liblockfile;

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::Test;

class VersionParserTest : public Test {
protected:
    virtual void SetUp() {
        auto version = std::make_unique<NiceMock<VersionInternalMock>>();
        version_ptr = version.get();

        EXPECT_CALL(version_factory, create()).WillOnce(Return(std::move(version)));

        EXPECT_CALL(yaml_node, get(_))
            .Times(AnyNumber())
            .WillRepeatedly([]() { return std::make_unique<NiceMock<YamlNodeMock>>(); });
    }

    NiceMock<VersionFactoryMock> version_factory;
    NiceMock<VersionInternalMock> * version_ptr;
    NiceMock<YamlNodeMock> yaml_node;

    VersionParser parser{version_factory};
};

TEST_F(VersionParserTest, ParserSetsMajorValueFromYamlNode) {
    auto major_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto major_node_ptr = major_node.get();
    ON_CALL(*major_node, as_uint()).WillByDefault(Return(1));
    
    EXPECT_CALL(yaml_node, get("major")).WillOnce(Return(std::move(major_node)));
    EXPECT_CALL(*major_node_ptr, as_uint());
    EXPECT_CALL(*version_ptr, set_major(1));
    parser.parse(yaml_node);
}

TEST_F(VersionParserTest, ParserSetsMinorValueFromYamlNode) {
    auto minor_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto minor_node_ptr = minor_node.get();
    ON_CALL(*minor_node, as_uint()).WillByDefault(Return(4));

    EXPECT_CALL(yaml_node, get("minor")).WillOnce(Return(std::move(minor_node)));
    EXPECT_CALL(*minor_node_ptr, as_uint());
    EXPECT_CALL(*version_ptr, set_minor(4));
    parser.parse(yaml_node);
}

TEST_F(VersionParserTest, ParserSetsPatchValueFromYamlNode) {
    auto patch_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto patch_node_ptr = patch_node.get();
    ON_CALL(*patch_node, as_uint()).WillByDefault(Return(7));

    EXPECT_CALL(yaml_node, get("patch")).WillOnce(Return(std::move(patch_node)));
    EXPECT_CALL(*patch_node_ptr, as_uint());
    EXPECT_CALL(*version_ptr, set_patch(7));
    parser.parse(yaml_node);
}

TEST_F(VersionParserTest, ParserReturnsTheObjectCreatedByFactory) {
    auto parsed_version = parser.parse(yaml_node);
    EXPECT_EQ(parsed_version.get(), version_ptr);
}

}