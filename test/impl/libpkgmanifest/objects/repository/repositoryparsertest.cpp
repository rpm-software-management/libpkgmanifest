#include "libpkgmanifest/mocks/objects/repository/repositorymock.hpp"
#include "libpkgmanifest/mocks/objects/repository/repositoryfactorymock.hpp"
#include "libpkgmanifest/mocks/yaml/yamlnodemock.hpp"

#include "libpkgmanifest/objects/repository/repositoryparser.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal;

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::Test;

class RepositoryParserTest : public Test {
protected:
    virtual void SetUp() {
        auto repository = std::make_unique<NiceMock<RepositoryMock>>();
        repository_ptr = repository.get();

        auto repository_factory = std::make_shared<NiceMock<RepositoryFactoryMock>>();
        EXPECT_CALL(*repository_factory, create()).WillOnce(Return(std::move(repository)));

        EXPECT_CALL(yaml_node, get(_))
            .Times(AnyNumber())
            .WillRepeatedly([]() { return std::make_unique<NiceMock<YamlNodeMock>>(); });

        parser = std::make_unique<RepositoryParser>(repository_factory);
    }

    NiceMock<RepositoryMock> * repository_ptr;
    NiceMock<YamlNodeMock> yaml_node;

    std::unique_ptr<RepositoryParser> parser;
};

TEST_F(RepositoryParserTest, ParserSetsIdFromYamlNode) {
    auto id_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto id_node_ptr = id_node.get();
    
    EXPECT_CALL(yaml_node, get("id")).WillOnce(Return(std::move(id_node)));
    EXPECT_CALL(*id_node_ptr, as_string()).WillOnce(Return("repo1"));
    EXPECT_CALL(*repository_ptr, set_id("repo1"));
    parser->parse(yaml_node);
}

TEST_F(RepositoryParserTest, ParserSetsUrlFromYamlNode) {
    auto url_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto url_node_ptr = url_node.get();
    
    EXPECT_CALL(yaml_node, get("url")).WillOnce(Return(std::move(url_node)));
    EXPECT_CALL(*url_node_ptr, as_string()).WillOnce(Return("urly urlish url"));
    EXPECT_CALL(*repository_ptr, set_url("urly urlish url"));
    parser->parse(yaml_node);
}

TEST_F(RepositoryParserTest, ParserReturnsTheObjectCreatedByFactory) {
    auto parsed_repository = parser->parse(yaml_node);
    EXPECT_EQ(parsed_repository.get(), repository_ptr);
}

}