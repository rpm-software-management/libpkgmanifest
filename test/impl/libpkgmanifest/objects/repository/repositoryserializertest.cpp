#include "impl/libpkgmanifest/mocks/objects/repository/repositorymock.hpp"
#include "impl/libpkgmanifest/mocks/yaml/yamlnodefactorymock.hpp"
#include "impl/libpkgmanifest/mocks/yaml/yamlnodemock.hpp"
#include "impl/libpkgmanifest/mocks/yaml/yamlnodeinternalmock.hpp"
#include "impl/libpkgmanifest/mocks/yaml/yamlnodeinternalstub.hpp"

#include "impl/libpkgmanifest/objects/repository/repositoryserializer.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal;

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

TEST_F(RepositorySerializerTest, SerializerSetsUrlAsStringToYamlNode) {
    EXPECT_CALL(repository, get_url()).WillOnce(Return("address"));

    EXPECT_CALL(*node_ptr, insert("url", _)).WillOnce(
    [](const std::string &, std::unique_ptr<IYamlNode> node) {
        EXPECT_EQ("address", node->as_string());
    });

    serializer->serialize(repository);
}

TEST_F(RepositorySerializerTest, SerializerReturnsTheObjectCreatedByFactory) {
    auto serialized_node = serializer->serialize(repository);
    EXPECT_EQ(serialized_node.get(), node_ptr);
}

}