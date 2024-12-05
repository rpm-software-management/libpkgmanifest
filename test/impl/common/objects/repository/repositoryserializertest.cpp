#include "impl/common/mocks/objects/repository/repositorymock.hpp"
#include "impl/common/mocks/yaml/yamlnodefactorymock.hpp"
#include "impl/common/mocks/yaml/yamlnodemock.hpp"
#include "impl/common/mocks/yaml/yamlnodeinternalmock.hpp"
#include "impl/common/mocks/yaml/yamlnodeinternalstub.hpp"

#include "impl/common/objects/repository/repositoryserializer.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal::common;

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::NiceMock;
using ::testing::Pointer;
using ::testing::Ref;
using ::testing::Return;
using ::testing::ReturnPointee;
using ::testing::Test;

class RepositorySerializerTest : public Test {
protected:
    virtual void SetUp() {
        auto node = std::make_unique<NiceMock<YamlNodeInternalMock>>();
        node_ptr = node.get();
        EXPECT_CALL(*node_ptr, insert(_, _)).Times(AnyNumber());

        auto node_factory = std::make_shared<NiceMock<YamlNodeFactoryMock>>();
        EXPECT_CALL(*node_factory, create())
            .WillOnce(Return(std::move(node)))
            .WillRepeatedly([]() { 
                return std::make_unique<YamlNodeInternalStub>(); 
            });
        
        serializer = std::make_unique<RepositorySerializer>(node_factory);
    }

    NiceMock<RepositoryMock> repository;
    NiceMock<YamlNodeInternalMock> * node_ptr;
    std::unique_ptr<RepositorySerializer> serializer;
};

TEST_F(RepositorySerializerTest, SerializerSetsIdAsStringToYamlNode) {
    EXPECT_CALL(repository, get_id()).WillOnce(Return("repo1"));

    EXPECT_CALL(*node_ptr, insert("id", _)).WillOnce(
        [](const std::string &, std::unique_ptr<IYamlNode> node) {
            EXPECT_EQ("repo1", node->as_string());
        });

    serializer->serialize(repository);
}

TEST_F(RepositorySerializerTest, SerializerSetsBaseurlAsStringToYamlNode) {
    EXPECT_CALL(repository, get_baseurl()).WillOnce(Return("address"));

    EXPECT_CALL(*node_ptr, insert("baseurl", _)).WillOnce(
    [](const std::string &, std::unique_ptr<IYamlNode> node) {
        EXPECT_EQ("address", node->as_string());
    });

    serializer->serialize(repository);
}

TEST_F(RepositorySerializerTest, SerializerDoesNotSetBaseurlIfEmpty) {
    EXPECT_CALL(repository, get_baseurl()).WillOnce(Return(""));
    EXPECT_CALL(*node_ptr, insert("baseurl", _)).Times(0);

    serializer->serialize(repository);
}

TEST_F(RepositorySerializerTest, SerializerSetsMetalinkAsStringToYamlNode) {
    EXPECT_CALL(repository, get_metalink()).WillOnce(Return("meta_address"));

    EXPECT_CALL(*node_ptr, insert("metalink", _)).WillOnce(
    [](const std::string &, std::unique_ptr<IYamlNode> node) {
        EXPECT_EQ("meta_address", node->as_string());
    });

    serializer->serialize(repository);
}

TEST_F(RepositorySerializerTest, SerializerDoesNotSetMetalinkIfEmpty) {
    EXPECT_CALL(repository, get_metalink()).WillOnce(Return(""));
    EXPECT_CALL(*node_ptr, insert("metalink", _)).Times(0);

    serializer->serialize(repository);
}

TEST_F(RepositorySerializerTest, SerializerSetsMirrorlistAsStringToYamlNode) {
    EXPECT_CALL(repository, get_mirrorlist()).WillOnce(Return("mirrors"));

    EXPECT_CALL(*node_ptr, insert("mirrorlist", _)).WillOnce(
    [](const std::string &, std::unique_ptr<IYamlNode> node) {
        EXPECT_EQ("mirrors", node->as_string());
    });

    serializer->serialize(repository);
}

TEST_F(RepositorySerializerTest, SerializerDoesNotSetMirrorlistIfEmpty) {
    EXPECT_CALL(repository, get_mirrorlist()).WillOnce(Return(""));
    EXPECT_CALL(*node_ptr, insert("mirrorlist", _)).Times(0);

    serializer->serialize(repository);
}

TEST_F(RepositorySerializerTest, SerializerReturnsTheObjectCreatedByFactory) {
    auto serialized_node = serializer->serialize(repository);
    EXPECT_EQ(serialized_node.get(), node_ptr);
}

}