// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/common/mocks/yaml/yamlnodemock.hpp"

#include "impl/common/yaml/yamlnode.hpp"
#include "impl/common/yaml/yamlserializer.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>

namespace {

using namespace libpkgmanifest::internal::common;

using ::testing::NiceMock;
using ::testing::Test;

class YamlSerializerTest : public Test {
protected:
    virtual void SetUp() {
        file_path = std::filesystem::temp_directory_path() / "YamlSerializerTest.yaml";
    }

    virtual void TearDown() {
        std::error_code ec;
        std::filesystem::remove(file_path, ec);
    }

    std::filesystem::path file_path;
};

TEST_F(YamlSerializerTest, SerializeSimpleYamlToFile) {
    YamlNode node;
    node.set("value");

    YamlSerializer serializer;
    serializer.to_file(node, file_path.string());

    std::ifstream file_stream(file_path);
    std::string content((std::istreambuf_iterator<char>(file_stream)), std::istreambuf_iterator<char>());

    EXPECT_EQ("value", content);
}

TEST_F(YamlSerializerTest, SerializeSimpleYamlToFileWithUnknownNodeImplThrowsException) {
    NiceMock<YamlNodeMock> node;
    YamlSerializer serializer;
    EXPECT_THROW(serializer.to_file(node, "unknown_path"), std::runtime_error);
}

TEST_F(YamlSerializerTest, SerializeSimpleYamlToFileWithInvalidPathThrowsException) {
    YamlNode node;
    node.set("value");

    YamlSerializer serializer;
    EXPECT_THROW(serializer.to_file(node, "/"), FileOutputError);
}

TEST_F(YamlSerializerTest, SerializeSimpleYamlToString) {
    YamlNode node;
    node.set("value");

    YamlSerializer serializer;
    auto content = serializer.to_string(node);

    EXPECT_EQ("value", content);
}

TEST_F(YamlSerializerTest, SerializeSimpleYamlToStringWithUnknownNodeImplThrowsException) {
    EXPECT_THROW(YamlSerializer().to_string(NiceMock<YamlNodeMock>()), std::runtime_error);
}

}