// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/common/yaml/yamlparser.hpp"

#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal::common;

TEST(YamlParserTest, ParseInvalidYamlFromStringThrowsAnException) {
    YamlParser parser;
    EXPECT_THROW(parser.from_string("["), YamlParseError);
}

TEST(YamlParserTest, ParseInvalidYamlFromFileThrowsAnException) {
    auto file_path = std::string(getenv("PROJECT_SOURCE_DIR")) + "/test/data/manifest/invalid.yaml";
    YamlParser parser;
    EXPECT_THROW(parser.from_file(file_path), YamlParseError);
}

TEST(YamlParserTest, ParseNonExistingYamlFileThrowsAnException) {
    YamlParser parser;
    EXPECT_THROW(parser.from_file("non-existing-manifest.yaml"), YamlFileError);
}

}