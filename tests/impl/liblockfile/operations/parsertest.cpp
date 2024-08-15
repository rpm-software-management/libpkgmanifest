#include "liblockfile/mocks/objects/lockfile/lockfilemock.hpp"
#include "liblockfile/mocks/objects/lockfile/lockfileparsermock.hpp"
#include "liblockfile/mocks/yaml/yamlnodemock.hpp"
#include "liblockfile/mocks/yaml/yamlparsermock.hpp"

#include "liblockfile/operations/parser.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace liblockfile::internal;

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Return;

TEST(ParserTest, NodeFromYamlParserIsPassedToLockFileParser) {
    auto yaml_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto yaml_node_ptr = yaml_node.get();
    auto lock_file = std::make_unique<NiceMock<LockFileMock>>();
    auto lock_file_ptr = lock_file.get();
    auto file_parser = std::make_unique<NiceMock<LockFileParserMock>>();
    auto file_parser_ptr = file_parser.get();
    auto yaml_parser = std::make_unique<NiceMock<YamlParserMock>>();
    auto yaml_parser_ptr = yaml_parser.get();

    Parser parser(std::move(yaml_parser), std::move(file_parser));

    EXPECT_CALL(*yaml_parser_ptr, from_file(_)).WillOnce(Return(std::move(yaml_node)));
    EXPECT_CALL(*file_parser_ptr, parse(Ref(*yaml_node_ptr))).WillOnce(Return(std::move(lock_file)));

    auto parsed_file = parser.parse("path");
    EXPECT_EQ(parsed_file.get(), lock_file_ptr);
}

}