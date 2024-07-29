#include "liblockfile/mocks/objects/checksum/checksummock.hpp"
#include "liblockfile/mocks/yaml/yamlnodefactorymock.hpp"
#include "liblockfile/mocks/yaml/yamlnodeinternalmock.hpp"

#include "liblockfile/objects/checksum/checksumserializer.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace liblockfile::internal;

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::Test;

class ChecksumSerializerTest : public Test {
protected:
    virtual void SetUp() {
        auto node = std::make_unique<NiceMock<YamlNodeInternalMock>>();
        node_ptr = node.get();

        auto node_factory = std::make_shared<NiceMock<YamlNodeFactoryMock>>();
        EXPECT_CALL(*node_factory, create()).WillOnce(Return(std::move(node)));

        serializer = std::make_unique<ChecksumSerializer>(node_factory);
    }

    NiceMock<YamlNodeInternalMock> * node_ptr;
    std::unique_ptr<ChecksumSerializer> serializer;
};

TEST_F(ChecksumSerializerTest, SerializerSetsCRC32MethodAndDigestAsStringToYamlNode) {
    NiceMock<ChecksumMock> checksum;
    EXPECT_CALL(checksum, get_method()).WillOnce(Return(ChecksumMethod::CRC32));
    EXPECT_CALL(checksum, get_digest()).WillOnce(Return("digest"));
    EXPECT_CALL(*node_ptr, set("crc32:digest"));
    serializer->serialize(checksum);
}

TEST_F(ChecksumSerializerTest, SerializerSetsCRC64MethodAndDigestAsStringToYamlNode) {
    NiceMock<ChecksumMock> checksum;
    EXPECT_CALL(checksum, get_method()).WillOnce(Return(ChecksumMethod::CRC64));
    EXPECT_CALL(checksum, get_digest()).WillOnce(Return("abcdef"));
    EXPECT_CALL(*node_ptr, set("crc64:abcdef"));
    serializer->serialize(checksum);
}

TEST_F(ChecksumSerializerTest, SerializerSetsMD5MethodAndDigestAsStringToYamlNode) {
    NiceMock<ChecksumMock> checksum;
    EXPECT_CALL(checksum, get_method()).WillOnce(Return(ChecksumMethod::MD5));
    EXPECT_CALL(checksum, get_digest()).WillOnce(Return("a1a1a1a1a1a1a1"));
    EXPECT_CALL(*node_ptr, set("md5:a1a1a1a1a1a1a1"));
    serializer->serialize(checksum);
}

TEST_F(ChecksumSerializerTest, SerializerSetsSHA256MethodAndDigestAsStringToYamlNode) {
    NiceMock<ChecksumMock> checksum;
    EXPECT_CALL(checksum, get_method()).WillOnce(Return(ChecksumMethod::SHA256));
    EXPECT_CALL(checksum, get_digest()).WillOnce(Return("sha256digest"));
    EXPECT_CALL(*node_ptr, set("sha256:sha256digest"));
    serializer->serialize(checksum);
}

TEST_F(ChecksumSerializerTest, SerializerSetsSHA512MethodAndDigestAsStringToYamlNode) {
    NiceMock<ChecksumMock> checksum;
    EXPECT_CALL(checksum, get_method()).WillOnce(Return(ChecksumMethod::SHA512));
    EXPECT_CALL(checksum, get_digest()).WillOnce(Return("ababababababab"));
    EXPECT_CALL(*node_ptr, set("sha512:ababababababab"));
    serializer->serialize(checksum);
}

TEST_F(ChecksumSerializerTest, SerializerReturnsTheObjectCreatedByFactory) {
    NiceMock<ChecksumMock> checksum;
    auto serialized_node = serializer->serialize(checksum);
    EXPECT_EQ(serialized_node.get(), node_ptr);
}

}