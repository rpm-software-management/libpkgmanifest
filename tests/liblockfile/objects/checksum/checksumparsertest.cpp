#include "liblockfile/mocks/objects/checksum/checksumfactorymock.hpp"
#include "liblockfile/mocks/objects/checksum/checksuminternalmock.hpp"
#include "liblockfile/mocks/yaml/yamlnodemock.hpp"

#include "liblockfile/objects/checksum/checksumparser.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace liblockfile;

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::Test;

class ChecksumParserTest : public Test {
protected:
    virtual void SetUp() {
        auto checksum = std::make_unique<NiceMock<ChecksumInternalMock>>();
        checksum_ptr = checksum.get();

        EXPECT_CALL(checksum_factory, create()).WillOnce(Return(std::move(checksum)));
    }

    NiceMock<ChecksumFactoryMock> checksum_factory;
    NiceMock<ChecksumInternalMock> * checksum_ptr;
    NiceMock<YamlNodeMock> yaml_node;

    ChecksumParser parser{checksum_factory};
};

TEST_F(ChecksumParserTest, ParserSetsSHA256MethodFromYamlNode) {
    ON_CALL(yaml_node, as_string()).WillByDefault(Return("SHA256:aaabbb"));

    EXPECT_CALL(yaml_node, as_string());
    EXPECT_CALL(*checksum_ptr, set_method(ChecksumMethod::SHA256));
    parser.parse(yaml_node);
}

TEST_F(ChecksumParserTest, ParserSetsSHA512MethodFromYamlNode) {
    ON_CALL(yaml_node, as_string()).WillByDefault(Return("SHA512:abcdefgh"));

    EXPECT_CALL(yaml_node, as_string());
    EXPECT_CALL(*checksum_ptr, set_method(ChecksumMethod::SHA512));
    parser.parse(yaml_node);
}

TEST_F(ChecksumParserTest, ParserSetsMD5MethodFromYamlNode) {
    ON_CALL(yaml_node, as_string()).WillByDefault(Return("MD5:hgfedcba"));

    EXPECT_CALL(yaml_node, as_string());
    EXPECT_CALL(*checksum_ptr, set_method(ChecksumMethod::MD5));
    parser.parse(yaml_node);
}

TEST_F(ChecksumParserTest, ParserSetsCRC32MethodFromYamlNode) {
    ON_CALL(yaml_node, as_string()).WillByDefault(Return("CRC32:bcxbxcvx"));

    EXPECT_CALL(yaml_node, as_string());
    EXPECT_CALL(*checksum_ptr, set_method(ChecksumMethod::CRC32));
    parser.parse(yaml_node);
}

TEST_F(ChecksumParserTest, ParserSetsCRC64MethodFromYamlNode) {
    ON_CALL(yaml_node, as_string()).WillByDefault(Return("CRC64:nvnccf"));

    EXPECT_CALL(yaml_node, as_string());
    EXPECT_CALL(*checksum_ptr, set_method(ChecksumMethod::CRC64));
    parser.parse(yaml_node);
}

TEST_F(ChecksumParserTest, ParserSetsLowercaseMethodFromYamlNode) {
    ON_CALL(yaml_node, as_string()).WillByDefault(Return("sha512:bcxvf"));

    EXPECT_CALL(yaml_node, as_string());
    EXPECT_CALL(*checksum_ptr, set_method(ChecksumMethod::SHA512));
    parser.parse(yaml_node);
}

TEST_F(ChecksumParserTest, ParserSetsDigestFromYamlNode) {
    ON_CALL(yaml_node, as_string()).WillByDefault(Return("dontcare:abcdefg"));

    EXPECT_CALL(yaml_node, as_string());
    EXPECT_CALL(*checksum_ptr, set_digest("abcdefg"));
    parser.parse(yaml_node);
}

TEST_F(ChecksumParserTest, ParserReturnsTheObjectCreatedByFactory) {
    auto parsed_checksum = parser.parse(yaml_node);
    EXPECT_EQ(parsed_checksum.get(), checksum_ptr);
}

}