// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/common/mocks/objects/repository/repositorymock.hpp"
#include "impl/common/mocks/objects/repository/repositoryparsermock.hpp"
#include "impl/common/mocks/objects/repositories/repositoriesfactorymock.hpp"
#include "impl/common/mocks/objects/repositories/repositoriesmock.hpp"
#include "impl/common/mocks/yaml/yamlnodemock.hpp"

#include "impl/common/objects/repositories/repositoriesparser.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal::common;

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Pointer;
using ::testing::Ref;
using ::testing::Return;
using ::testing::Test;

class RepositoriesParserTest : public Test {
protected:
    virtual void SetUp() {
        auto repositories = std::make_unique<NiceMock<RepositoriesMock>>();
        repositories_ptr = repositories.get();

        auto repositories_factory_wrapper = std::make_shared<NiceMock<RepositoriesFactoryMock>>();
        EXPECT_CALL(*repositories_factory_wrapper, create()).WillOnce(Return(std::move(repositories)));

        auto repository_parser_wrapper = std::make_unique<NiceMock<RepositoryParserMock>>();
        repository_parser = repository_parser_wrapper.get();

        parser = std::make_unique<RepositoriesParser>(
            std::move(repository_parser_wrapper),
            repositories_factory_wrapper
        );
    }

    NiceMock<RepositoryParserMock> * repository_parser;
    NiceMock<RepositoriesMock> * repositories_ptr;
    NiceMock<YamlNodeMock> yaml_node;

    std::unique_ptr<RepositoriesParser> parser;
};

TEST_F(RepositoriesParserTest, ParserAddsAllRepositoriesForEachIdInYamlNode) {
    auto repo1_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto repo1_node_ptr = repo1_node.get();
    auto repo2_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto repo2_node_ptr = repo2_node.get();
    auto repo1 = std::make_unique<NiceMock<RepositoryMock>>();
    auto repo1_ptr = repo1.get();
    auto repo2 = std::make_unique<NiceMock<RepositoryMock>>();
    auto repo2_ptr = repo2.get();

    std::vector<std::unique_ptr<IYamlNode>> nodes_list;
    nodes_list.push_back(std::move(repo1_node));
    nodes_list.push_back(std::move(repo2_node));

    EXPECT_CALL(yaml_node, as_list()).WillOnce(Return(std::move(nodes_list)));

    EXPECT_CALL(*repository_parser, parse(Ref(*repo1_node_ptr))).WillOnce(Return(std::move(repo1)));
    EXPECT_CALL(*repository_parser, parse(Ref(*repo2_node_ptr))).WillOnce(Return(std::move(repo2)));

    EXPECT_CALL(*repositories_ptr, add(Pointer(repo1_ptr)));
    EXPECT_CALL(*repositories_ptr, add(Pointer(repo2_ptr)));

    parser->parse(yaml_node);
}

TEST_F(RepositoriesParserTest, ParserReturnsTheObjectCreatedByFactory) {
    auto parsed_repositories = parser->parse(yaml_node);
    EXPECT_EQ(parsed_repositories.get(), repositories_ptr);
}

}