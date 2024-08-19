#include "liblockfile/mocks/objects/version/versionfactorymock.hpp"
#include "liblockfile/mocks/objects/version/versionmock.hpp"
#include "liblockfile/mocks/tools/stringsplittermock.hpp"
#include "liblockfile/mocks/yaml/yamlnodemock.hpp"

#include "liblockfile/objects/version/versionparser.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace liblockfile::internal;

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::Test;

class VersionParserTest : public Test {
protected:
    virtual void SetUp() {
        auto version = std::make_unique<NiceMock<VersionMock>>();
        version_ptr = version.get();

        auto version_factory_wrapper = std::make_unique<NiceMock<VersionFactoryMock>>();
        EXPECT_CALL(*version_factory_wrapper, create()).WillOnce(Return(std::move(version)));

        EXPECT_CALL(yaml_node, get(_))
            .Times(AnyNumber())
            .WillRepeatedly([]() { return std::make_unique<NiceMock<YamlNodeMock>>(); });
        
        string_splitter = std::make_shared<NiceMock<StringSplitterMock>>();
        parser = std::make_unique<VersionParser>(std::move(version_factory_wrapper), string_splitter);
    }

    std::shared_ptr<NiceMock<StringSplitterMock>> string_splitter;

    NiceMock<VersionMock> * version_ptr;
    NiceMock<YamlNodeMock> yaml_node;

    std::unique_ptr<VersionParser> parser;
};

TEST_F(VersionParserTest, ParserSetsMajorValueFromSingleValue) {
    EXPECT_CALL(yaml_node, as_string()).WillOnce(Return("1"));
    EXPECT_CALL(*string_splitter, split("1", '.')).WillOnce(Return(std::vector<std::string>{"1"}));
    EXPECT_CALL(*version_ptr, set_major(1));
    parser->parse(yaml_node);
}

TEST_F(VersionParserTest, ParserSetsMajorAndMinorValueFromTwoValues) {
    EXPECT_CALL(yaml_node, as_string()).WillOnce(Return("1.2"));
    EXPECT_CALL(*string_splitter, split("1.2", '.')).WillOnce(Return(std::vector<std::string>{"1", "2"}));
    EXPECT_CALL(*version_ptr, set_major(1));
    EXPECT_CALL(*version_ptr, set_minor(2));
    parser->parse(yaml_node);
}

TEST_F(VersionParserTest, ParserSetsAllVersionPartsFromThreeValues) {
    EXPECT_CALL(yaml_node, as_string()).WillOnce(Return("1.2.3"));
    EXPECT_CALL(*string_splitter, split("1.2.3", '.')).WillOnce(Return(std::vector<std::string>{"1", "2", "3"}));
    EXPECT_CALL(*version_ptr, set_major(1));
    EXPECT_CALL(*version_ptr, set_minor(2));
    EXPECT_CALL(*version_ptr, set_patch(3));
    parser->parse(yaml_node);
}

TEST_F(VersionParserTest, ParserReturnsTheObjectCreatedByFactory) {
    auto parsed_version = parser->parse(yaml_node);
    EXPECT_EQ(parsed_version.get(), version_ptr);
}

}