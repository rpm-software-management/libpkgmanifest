#include "yaml/yamlnode.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace liblockfile;

using ::testing::ElementsAre;

TEST(YamlNodeTest, ParseNonExistingItemFromYamlThrowsAnException) {
    YamlNode node(YAML::Load(""));
    EXPECT_THROW(node.get("key"), YamlUnknownKeyError);
}

TEST(YamlNodeTest, ParseNodeFromYaml) {
    YamlNode node(YAML::Load("string_item: \"value\""));
    EXPECT_EQ("value", node.get("string_item")->as_string());
}

TEST(YamlNodeTest, ParseStringFromYaml) {
    YamlNode node(YAML::Load("\"value\""));
    EXPECT_EQ("value", node.as_string());
}

TEST(YamlNodeTest, ParseIntegerFromYaml) {
    YamlNode node(YAML::Load("-5"));
    EXPECT_EQ(-5, node.as_int());
}

TEST(YamlNodeTest, ParseInvalidIntegerValueFromYamlThrowsAnException) {
    YamlNode node(YAML::Load("abcd"));
    EXPECT_THROW(node.as_int(), YamlInvalidValueConversionError);
}

TEST(YamlNodeTest, ParseUnsignedLongIntegerFromYaml) {
    YamlNode node(YAML::Load("6123456789012345678"));
    EXPECT_EQ(6123456789012345678, node.as_uint64());
}

TEST(YamlNodeTest, ParseInvalidUnsignedLongIntegerValueFromYamlThrowsAnException) {
    YamlNode node(YAML::Load("-1"));
    EXPECT_THROW(node.as_uint64(), YamlInvalidValueConversionError);
}

TEST(YamlNodeTest, ParseSimpleListFromYaml) {
    YamlNode node(YAML::Load("[1, 2, 3, 4]"));
    auto list = node.as_list();
    std::vector<int> int_list(list.size());
    std::transform(list.begin(), list.end(), int_list.begin(), [](const std::unique_ptr<IYamlNode> & node) {
        return node->as_int();
    });
    EXPECT_THAT(int_list, ElementsAre(1, 2, 3, 4));
}

TEST(YamlNodeTest, ParseComplexListFromYaml) {
    const std::string complex_list_yaml = R"(
        - field1: "abcd"
          field2: 111
        - field1: "efgh"
          field2: 112
    )";

    YamlNode node(YAML::Load(complex_list_yaml));
    auto list = node.as_list();

    EXPECT_EQ(2, list.size());
    EXPECT_EQ("abcd", list[0]->get("field1")->as_string());
    EXPECT_EQ(111, list[0]->get("field2")->as_int());
    EXPECT_EQ("efgh", list[1]->get("field1")->as_string());
    EXPECT_EQ(112, list[1]->get("field2")->as_int());
}

}