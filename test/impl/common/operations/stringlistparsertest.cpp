#include "impl/common/mocks/yaml/yamlnodemock.hpp"

#include "impl/common/operations/stringlistparser/stringlistparser.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal::common;

using ::testing::ElementsAre;
using ::testing::NiceMock;
using ::testing::Return;

TEST(StringListParserTest, ParseAddsAllListItemsToTheOutputVector) {
    std::vector<std::unique_ptr<IYamlNode>> items_nodes; 
    auto item1_node = std::make_unique<NiceMock<YamlNodeMock>>();
    EXPECT_CALL(*item1_node, as_string()).WillOnce(Return("item1"));
    auto item2_node = std::make_unique<NiceMock<YamlNodeMock>>();
    EXPECT_CALL(*item2_node, as_string()).WillOnce(Return("item2"));
    items_nodes.push_back(std::move(item1_node));
    items_nodes.push_back(std::move(item2_node));

    NiceMock<YamlNodeMock> node;
    EXPECT_CALL(node, as_list()).WillOnce(Return(std::move(items_nodes)));

    StringListParser parser;
    auto result = parser.parse(node);
    EXPECT_THAT(result, ElementsAre("item1", "item2"));
}

}