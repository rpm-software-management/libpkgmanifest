#include "impl/common/mocks/objects/repository/repositorymock.hpp"
#include "impl/common/mocks/objects/repository/repositoryfactorymock.hpp"
#include "impl/common/mocks/yaml/yamlnodemock.hpp"

#include "impl/common/objects/repository/repositoryparser.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal::common;

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
        
        EXPECT_CALL(yaml_node, has(_)).Times(AnyNumber()).WillRepeatedly(Return(false));

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

TEST_F(RepositoryParserTest, ParserSetsBaseurlFromYamlNode) {
    auto baseurl_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto baseurl_node_ptr = baseurl_node.get();
    
    EXPECT_CALL(yaml_node, has("baseurl")).WillOnce(Return(true));
    EXPECT_CALL(yaml_node, get("baseurl")).WillOnce(Return(std::move(baseurl_node)));
    EXPECT_CALL(*baseurl_node_ptr, as_string()).WillOnce(Return("urly urlish url"));
    EXPECT_CALL(*repository_ptr, set_baseurl("urly urlish url"));
    parser->parse(yaml_node);
}

TEST_F(RepositoryParserTest, ParserSetsMetalinkFromYamlNode) {
    auto metalink_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto metalink_node_ptr = metalink_node.get();
    
    EXPECT_CALL(yaml_node, has("metalink")).WillOnce(Return(true));
    EXPECT_CALL(yaml_node, get("metalink")).WillOnce(Return(std::move(metalink_node)));
    EXPECT_CALL(*metalink_node_ptr, as_string()).WillOnce(Return("metalink"));
    EXPECT_CALL(*repository_ptr, set_metalink("metalink"));
    parser->parse(yaml_node);
}

TEST_F(RepositoryParserTest, ParserSetsMirrorlistFromYamlNode) {
    auto mirrorlist_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto mirrorlist_node_ptr = mirrorlist_node.get();
    
    EXPECT_CALL(yaml_node, has("mirrorlist")).WillOnce(Return(true));
    EXPECT_CALL(yaml_node, get("mirrorlist")).WillOnce(Return(std::move(mirrorlist_node)));
    EXPECT_CALL(*mirrorlist_node_ptr, as_string()).WillOnce(Return("mirrorlist"));
    EXPECT_CALL(*repository_ptr, set_mirrorlist("mirrorlist"));
    parser->parse(yaml_node);
}

TEST_F(RepositoryParserTest, ParserReturnsTheObjectCreatedByFactory) {
    auto parsed_repository = parser->parse(yaml_node);
    EXPECT_EQ(parsed_repository.get(), repository_ptr);
}

}