#include "liblockfile/mocks/objects/lockfile/lockfileinternalmock.hpp"
#include "liblockfile/mocks/objects/lockfile/lockfileparsermock.hpp"
#include "liblockfile/mocks/yaml/yamlnodemock.hpp"
#include "liblockfile/mocks/yaml/yamlparsermock.hpp"

#include "liblockfile/parser.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace liblockfile;

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::Test;

TEST(ParserTest, NodeFromYamlParserIsPassedToLockFileParser) {
    auto yaml_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto yaml_node_ptr = yaml_node.get();
    auto lock_file = std::make_unique<NiceMock<LockFileInternalMock>>();
    auto lock_file_ptr = lock_file.get();

    NiceMock<LockFileParserMock> file_parser;
    NiceMock<YamlParserMock> yaml_parser;

    Parser parser(yaml_parser, file_parser);

    EXPECT_CALL(yaml_parser, from_file(_)).WillOnce(Return(std::move(yaml_node)));
    EXPECT_CALL(file_parser, parse(Ref(*yaml_node_ptr))).WillOnce(Return(std::move(lock_file)));

    auto parsed_file = parser.parse("path");
    EXPECT_EQ(parsed_file.get(), lock_file_ptr);
}

}