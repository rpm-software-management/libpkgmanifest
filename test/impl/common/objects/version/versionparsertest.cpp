// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/common/mocks/objects/version/versionfactorymock.hpp"
#include "impl/common/mocks/objects/version/versionmock.hpp"
#include "impl/common/mocks/tools/stringsplittermock.hpp"
#include "impl/common/mocks/yaml/yamlnodemock.hpp"

#include "impl/common/objects/version/versionparser.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal::common;

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

        auto version_factory_wrapper = std::make_shared<NiceMock<VersionFactoryMock>>();
        EXPECT_CALL(*version_factory_wrapper, create()).WillOnce(Return(std::move(version)));

        EXPECT_CALL(yaml_node, get(_))
            .Times(AnyNumber())
            .WillRepeatedly([]() { return std::make_unique<NiceMock<YamlNodeMock>>(); });
        
        string_splitter = std::make_shared<NiceMock<StringSplitterMock>>();
        parser = std::make_unique<VersionParser>(version_factory_wrapper, string_splitter);
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

TEST_F(VersionParserTest, ParserThrowsAnExceptionWhenAnyPartIsNotANumber) {
    EXPECT_CALL(yaml_node, as_string()).WillOnce(Return("1.2.a"));
    EXPECT_CALL(*string_splitter, split("1.2.a", '.')).WillOnce(Return(std::vector<std::string>{"1", "2", "a"}));
    EXPECT_THROW(parser->parse(yaml_node), VersionFormatError);
}

TEST_F(VersionParserTest, ParserReturnsTheObjectCreatedByFactory) {
    auto parsed_version = parser->parse(yaml_node);
    EXPECT_EQ(parsed_version.get(), version_ptr);
}

}