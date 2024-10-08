#include "impl/libpkgmanifest/mocks/objects/repository/repositorymock.hpp"
#include "impl/libpkgmanifest/mocks/objects/repository/repositoryserializermock.hpp"
#include "impl/libpkgmanifest/mocks/objects/repositories/repositoriesmock.hpp"
#include "impl/libpkgmanifest/mocks/yaml/yamlnodefactorymock.hpp"
#include "impl/libpkgmanifest/mocks/yaml/yamlnodeinternalmock.hpp"
#include "impl/libpkgmanifest/mocks/yaml/yamlnodeinternalstub.hpp"

#include "impl/libpkgmanifest/objects/repositories/repositoriesserializer.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal;

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Pointer;
using ::testing::Ref;
using ::testing::Return;
using ::testing::ReturnPointee;
using ::testing::Test;

class RepositoriesSerializerTest : public Test {
protected:
    virtual void SetUp() {
        auto repository_serializer = std::make_unique<NiceMock<RepositorySerializerMock>>();
        repository_serializer_ptr = repository_serializer.get();

        auto node = std::make_unique<NiceMock<YamlNodeInternalMock>>();
        node_ptr = node.get();

        auto node_factory = std::make_shared<NiceMock<YamlNodeFactoryMock>>();
        EXPECT_CALL(*node_factory, create())
            .WillOnce(Return(std::move(node)))
            .WillRepeatedly([]() { 
                return std::make_unique<YamlNodeInternalStub>(); 
            });

        serializer = std::make_unique<RepositoriesSerializer>(node_factory, std::move(repository_serializer));
    }

    NiceMock<RepositoriesMock> repositories;
    NiceMock<YamlNodeInternalMock> * node_ptr;
    NiceMock<RepositorySerializerMock> * repository_serializer_ptr;
    std::unique_ptr<RepositoriesSerializer> serializer;
};

TEST_F(RepositoriesSerializerTest, SerializerCreatesListNodeForEachRepositoryFromSerializer) {
    auto repository1 = std::make_unique<NiceMock<RepositoryMock>>();
    auto repository1_ptr = repository1.get();
    auto repository1_node = std::make_unique<YamlNodeInternalStub>();
    auto repository1_node_ptr = repository1_node.get();
    repository1_node_ptr->set("repo1");

    auto repository2 = std::make_unique<NiceMock<RepositoryMock>>();
    auto repository2_ptr = repository2.get();
    auto repository2_node = std::make_unique<YamlNodeInternalStub>();
    auto repository2_node_ptr = repository2_node.get();
    repository2_node_ptr->set("repo2");

    EXPECT_CALL(*repository_serializer_ptr, serialize(Ref(*repository1_ptr)))
        .WillOnce(Return(std::move(repository1_node)));
    EXPECT_CALL(*repository_serializer_ptr, serialize(Ref(*repository2_ptr)))
        .WillOnce(Return(std::move(repository2_node)));

    std::map<std::string, std::unique_ptr<IRepository>> map;
    map["repo1"] = std::move(repository1);
    map["repo2"] = std::move(repository2);
    EXPECT_CALL(Const(repositories), get()).WillOnce(ReturnPointee(&map));

    EXPECT_CALL(*node_ptr, add(Pointer(repository1_node_ptr)));
    EXPECT_CALL(*node_ptr, add(Pointer(repository2_node_ptr)));

    serializer->serialize(repositories);
}

TEST_F(RepositoriesSerializerTest, SerializerReturnsTheObjectCreatedByFactory) {
    std::map<std::string, std::unique_ptr<IRepository>> map;
    EXPECT_CALL(Const(repositories), get()).WillOnce(ReturnPointee(&map));

    auto serialized_node = serializer->serialize(repositories);
    EXPECT_EQ(serialized_node.get(), node_ptr);
}

}