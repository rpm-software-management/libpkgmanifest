// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/manifest/mocks/objects/checksum/checksummock.hpp"
#include "impl/manifest/mocks/objects/checksum/checksumfactorymock.hpp"
#include "impl/common/mocks/tools/stringsplittermock.hpp"
#include "impl/common/mocks/yaml/yamlnodemock.hpp"

#include "impl/manifest/objects/checksum/checksumparser.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal::manifest;

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::Test;

class ChecksumParserTest : public Test {
protected:
    virtual void SetUp() {
        auto checksum = std::make_unique<NiceMock<ChecksumMock>>();
        checksum_ptr = checksum.get();

        auto checksum_factory = std::make_shared<NiceMock<ChecksumFactoryMock>>();
        EXPECT_CALL(*checksum_factory, create()).WillOnce(Return(std::move(checksum)));
    
        string_splitter = std::make_shared<NiceMock<StringSplitterMock>>();
        parser = std::make_unique<ChecksumParser>(checksum_factory, string_splitter);
    }

    std::shared_ptr<NiceMock<StringSplitterMock>> string_splitter;

    NiceMock<ChecksumMock> * checksum_ptr;
    NiceMock<YamlNodeMock> yaml_node;

    std::unique_ptr<ChecksumParser> parser;
};

TEST_F(ChecksumParserTest, ParserSetsSHA1MethodFromYamlNode) {
    EXPECT_CALL(yaml_node, as_string()).WillOnce(Return("SHA1:aaabbb"));
    EXPECT_CALL(*string_splitter, split("SHA1:aaabbb", ':')).WillOnce(
        Return(std::vector<std::string>{"SHA1", "aaabbb"})
    );
    EXPECT_CALL(*checksum_ptr, set_method(ChecksumMethod::SHA1));
    parser->parse(yaml_node);
}

TEST_F(ChecksumParserTest, ParserSetsSHA224MethodFromYamlNode) {
    EXPECT_CALL(yaml_node, as_string()).WillOnce(Return("SHA224:bbbaaa"));
    EXPECT_CALL(*string_splitter, split("SHA224:bbbaaa", ':')).WillOnce(
        Return(std::vector<std::string>{"SHA224", "bbbaaa"})
    );
    EXPECT_CALL(*checksum_ptr, set_method(ChecksumMethod::SHA224));
    parser->parse(yaml_node);
}

TEST_F(ChecksumParserTest, ParserSetsSHA256MethodFromYamlNode) {
    EXPECT_CALL(yaml_node, as_string()).WillOnce(Return("SHA256:aaabbb"));
    EXPECT_CALL(*string_splitter, split("SHA256:aaabbb", ':')).WillOnce(
        Return(std::vector<std::string>{"SHA256", "aaabbb"})
    );
    EXPECT_CALL(*checksum_ptr, set_method(ChecksumMethod::SHA256));
    parser->parse(yaml_node);
}

TEST_F(ChecksumParserTest, ParserSetsSHA384MethodFromYamlNode) {
    EXPECT_CALL(yaml_node, as_string()).WillOnce(Return("SHA384:dedede"));
    EXPECT_CALL(*string_splitter, split("SHA384:dedede", ':')).WillOnce(
        Return(std::vector<std::string>{"SHA384", "dedede"})
    );
    EXPECT_CALL(*checksum_ptr, set_method(ChecksumMethod::SHA384));
    parser->parse(yaml_node);
}

TEST_F(ChecksumParserTest, ParserSetsSHA512MethodFromYamlNode) {
    EXPECT_CALL(yaml_node, as_string()).WillOnce(Return("SHA512:abcdefgh"));
    EXPECT_CALL(*string_splitter, split("SHA512:abcdefgh", ':')).WillOnce(
        Return(std::vector<std::string>{"SHA512", "abcdefgh"})
    );
    EXPECT_CALL(*checksum_ptr, set_method(ChecksumMethod::SHA512));
    parser->parse(yaml_node);
}

TEST_F(ChecksumParserTest, ParserSetsMD5MethodFromYamlNode) {
    EXPECT_CALL(yaml_node, as_string()).WillOnce(Return("MD5:hgfedcba"));
    EXPECT_CALL(*string_splitter, split("MD5:hgfedcba", ':')).WillOnce(
        Return(std::vector<std::string>{"MD5", "hgfedcba"})
    );
    EXPECT_CALL(*checksum_ptr, set_method(ChecksumMethod::MD5));
    parser->parse(yaml_node);
}

TEST_F(ChecksumParserTest, ParserSetsCRC32MethodFromYamlNode) {
    EXPECT_CALL(yaml_node, as_string()).WillOnce(Return("CRC32:bcxbxcvx"));
    EXPECT_CALL(*string_splitter, split("CRC32:bcxbxcvx", ':')).WillOnce(
        Return(std::vector<std::string>{"CRC32", "bcxbxcvx"})
    );
    EXPECT_CALL(*checksum_ptr, set_method(ChecksumMethod::CRC32));
    parser->parse(yaml_node);
}

TEST_F(ChecksumParserTest, ParserSetsCRC64MethodFromYamlNode) {
    EXPECT_CALL(yaml_node, as_string()).WillOnce(Return("CRC64:nvnccf"));
    EXPECT_CALL(*string_splitter, split("CRC64:nvnccf", ':')).WillOnce(
        Return(std::vector<std::string>{"CRC64", "nvnccf"})
    );
    EXPECT_CALL(*checksum_ptr, set_method(ChecksumMethod::CRC64));
    parser->parse(yaml_node);
}

TEST_F(ChecksumParserTest, ParserSetsLowercaseMethodFromYamlNode) {
    EXPECT_CALL(yaml_node, as_string()).WillOnce(Return("sha512:bcxvf"));
    EXPECT_CALL(*string_splitter, split("sha512:bcxvf", ':')).WillOnce(
        Return(std::vector<std::string>{"sha512", "bcxvf"})
    );
    EXPECT_CALL(*checksum_ptr, set_method(ChecksumMethod::SHA512));
    parser->parse(yaml_node);
}

TEST_F(ChecksumParserTest, ParserSetsDigestFromYamlNode) {
    EXPECT_CALL(yaml_node, as_string()).WillOnce(Return("sha512:abcdefg"));
    EXPECT_CALL(*string_splitter, split("sha512:abcdefg", ':')).WillOnce(
        Return(std::vector<std::string>{"sha512", "abcdefg"})
    );
    EXPECT_CALL(*checksum_ptr, set_digest("abcdefg"));
    parser->parse(yaml_node);
}

TEST_F(ChecksumParserTest, ParserThrowsAnExceptionWhenChecksumFormatIsInvalid) {
    EXPECT_CALL(yaml_node, as_string()).WillOnce(Return("mimimimi"));
    EXPECT_CALL(*string_splitter, split("mimimimi", ':')).WillOnce(
        Return(std::vector<std::string>{"mimimimi"})
    );
    EXPECT_THROW(parser->parse(yaml_node), ChecksumFormatError);
}

TEST_F(ChecksumParserTest, ParserThrowsAnExceptionWhenChecksumMethodIsUnknown) {
    EXPECT_CALL(yaml_node, as_string()).WillOnce(Return("unknown:abcdefg"));
    EXPECT_CALL(*string_splitter, split("unknown:abcdefg", ':')).WillOnce(
        Return(std::vector<std::string>{"unknown", "abcdefg"})
    );
    EXPECT_THROW(parser->parse(yaml_node), ChecksumFormatError);
}

TEST_F(ChecksumParserTest, ParserReturnsTheObjectCreatedByFactory) {
    EXPECT_CALL(*string_splitter, split(_, _)).WillOnce(
        Return(std::vector<std::string>{"SHA256", "abcdefgh"})
    );

    auto parsed_checksum = parser->parse(yaml_node);
    EXPECT_EQ(parsed_checksum.get(), checksum_ptr);
}

}