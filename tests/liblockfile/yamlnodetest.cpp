#include "yamlnode.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>

namespace {

using namespace liblockfile;

TEST(YamlNodeTest, ParseNonExistingItemFromYamlThrowsAnException) {
    YamlNode node(YAML::Load(""));
    EXPECT_THROW(node.get("key"), YamlUnknownKeyError);
}

TEST(YamlNodeTest, ParseNodeFromYaml) {
    YamlNode node(YAML::Load("string_item: \"value\""));
    EXPECT_EQ("value", node.get("string_item")->as_string());
}

TEST(YamlNodeTest, ParseInnerNodeFromYaml) {
    // TODO
    // const std::string yaml = R"(
    //     item:
    //         nested_item: "value"
    // )";
    // YamlNode node(YAML::Load(yaml));
    // EXPECT_EQ("value", node.get("nested_item")->as_string());
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
    EXPECT_THAT(int_list, testing::ElementsAre(1, 2, 3, 4));
}

TEST(YamlNodeTest, ParseComplexListFromYaml) {
    // TODO
}

}