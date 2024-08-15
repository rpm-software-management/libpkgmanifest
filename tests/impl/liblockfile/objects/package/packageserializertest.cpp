#include "liblockfile/mocks/objects/checksum/checksummock.hpp"
#include "liblockfile/mocks/objects/checksum/checksumserializermock.hpp"
#include "liblockfile/mocks/objects/package/packagemock.hpp"
#include "liblockfile/mocks/yaml/yamlnodefactorymock.hpp"
#include "liblockfile/mocks/yaml/yamlnodemock.hpp"
#include "liblockfile/mocks/yaml/yamlnodeinternalmock.hpp"
#include "liblockfile/mocks/yaml/yamlnodeinternalstub.hpp"

#include "liblockfile/objects/package/packageserializer.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace liblockfile::internal;

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::NiceMock;
using ::testing::Pointer;
using ::testing::Ref;
using ::testing::Return;
using ::testing::ReturnPointee;
using ::testing::Test;

class PackageSerializerTest : public Test {
protected:
    virtual void SetUp() {
        auto checksum_serializer = std::make_unique<NiceMock<ChecksumSerializerMock>>();
        checksum_serializer_ptr = checksum_serializer.get();

        auto node = std::make_unique<NiceMock<YamlNodeInternalMock>>();
        node_ptr = node.get();
        EXPECT_CALL(*node_ptr, insert(_, _)).Times(AnyNumber());

        auto node_factory = std::make_shared<NiceMock<YamlNodeFactoryMock>>();
        EXPECT_CALL(*node_factory, create())
            .WillOnce(Return(std::move(node)))
            .WillRepeatedly([]() { 
                return std::make_unique<YamlNodeInternalStub>(); 
            });
        
        EXPECT_CALL(Const(package), get_checksum()).WillOnce(ReturnPointee(&checksum));

        serializer = std::make_unique<PackageSerializer>(node_factory, std::move(checksum_serializer));
    }

    NiceMock<PackageMock> package;
    NiceMock<ChecksumMock> checksum;
    NiceMock<YamlNodeInternalMock> * node_ptr;
    NiceMock<ChecksumSerializerMock> * checksum_serializer_ptr;
    std::unique_ptr<PackageSerializer> serializer;
};

TEST_F(PackageSerializerTest, SerializerSetsRepoIdAsStringToYamlNode) {
    EXPECT_CALL(package, get_repo_id()).WillOnce(Return("id"));

    EXPECT_CALL(*node_ptr, insert("repoid", _)).WillOnce(
        [](const std::string &, std::unique_ptr<IYamlNode> node) {
            EXPECT_EQ("id", node->as_string());
        });

    serializer->serialize(package);
}

TEST_F(PackageSerializerTest, SerializerSetsUrlAsStringToYamlNode) {
    EXPECT_CALL(package, get_url()).WillOnce(Return("address"));

    EXPECT_CALL(*node_ptr, insert("url", _)).WillOnce(
    [](const std::string &, std::unique_ptr<IYamlNode> node) {
        EXPECT_EQ("address", node->as_string());
    });

    serializer->serialize(package);
}

TEST_F(PackageSerializerTest, SerializerSetsChecksumFromChecksumSerializer) {
    auto checksum_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto checksum_node_ptr = checksum_node.get();
    EXPECT_CALL(*checksum_serializer_ptr, serialize(Ref(checksum))).WillOnce(Return(std::move(checksum_node)));

    EXPECT_CALL(*node_ptr, insert("checksum", Pointer(checksum_node_ptr)));

    serializer->serialize(package);
}

TEST_F(PackageSerializerTest, SerializerSetsSizeAsUInt64ToYamlNode) {
    EXPECT_CALL(package, get_size()).WillOnce(Return(123456789123456789U));

    EXPECT_CALL(*node_ptr, insert("size", _)).WillOnce(
    [](const std::string &, std::unique_ptr<IYamlNode> node) {
        EXPECT_EQ(123456789123456789U, node->as_uint64());
    });

    serializer->serialize(package);
}

TEST_F(PackageSerializerTest, SerializerSetsNevraAsStringToYamlNode) {
    EXPECT_CALL(package, get_nevra()).WillOnce(Return("a-1.0-1.fc40.x86_64"));

    EXPECT_CALL(*node_ptr, insert("nevra", _)).WillOnce(
    [](const std::string &, std::unique_ptr<IYamlNode> node) {
        EXPECT_EQ("a-1.0-1.fc40.x86_64", node->as_string());
    });

    serializer->serialize(package);
}

TEST_F(PackageSerializerTest, SerializerSetsSrpmAsStringToYamlNode) {
    EXPECT_CALL(package, get_srpm()).WillOnce(Return("a-1.0-1.fc40.src"));

    EXPECT_CALL(*node_ptr, insert("srpm", _)).WillOnce(
    [](const std::string &, std::unique_ptr<IYamlNode> node) {
        EXPECT_EQ("a-1.0-1.fc40.src", node->as_string());
    });

    serializer->serialize(package);
}

TEST_F(PackageSerializerTest, SerializerReturnsTheObjectCreatedByFactory) {
    auto serialized_node = serializer->serialize(package);
    EXPECT_EQ(serialized_node.get(), node_ptr);
}

}