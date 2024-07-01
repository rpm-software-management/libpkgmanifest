#include "liblockfile/yaml/yamlparser.hpp"

#include <gtest/gtest.h>

namespace {

using namespace liblockfile;

TEST(YamlParserTest, ParseInvalidYamlFromStringThrowsAnException) {
    YamlParser parser;
    EXPECT_THROW(parser.from_string("["), YamlParseError);
}

// TODO
// TEST(YamlParserTest, ParseInvalidYamlFromFileThrowsAnException) {
//     YamlParser parser;
//     EXPECT_THROW(parser.from_file("invalid.yaml"), YamlParseError);
// }

TEST(YamlParserTest, ParseNonExistingYamlFileThrowsAnException) {
    YamlParser parser;
    EXPECT_THROW(parser.from_file("non-existing-file.yaml"), YamlFileError);
}

}