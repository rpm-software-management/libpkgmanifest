#include "impl/libpkgmanifest/mocks/objects/input/inputmock.hpp"
#include "impl/libpkgmanifest/mocks/objects/input/inputparsermock.hpp"
#include "impl/libpkgmanifest/mocks/objects/manifest/manifestmock.hpp"
#include "impl/libpkgmanifest/mocks/objects/manifest/manifestparsermock.hpp"
#include "impl/libpkgmanifest/mocks/operations/prototypeinfileconvertermock.hpp"
#include "impl/libpkgmanifest/mocks/yaml/yamlnodemock.hpp"
#include "impl/libpkgmanifest/mocks/yaml/yamlparsermock.hpp"

#include "impl/libpkgmanifest/operations/parser.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal;

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Return;

TEST(ParserTest, ParseManifestPassesYamlNodeToManifestParser) {
    auto yaml_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto yaml_node_ptr = yaml_node.get();
    auto manifest = std::make_unique<NiceMock<ManifestMock>>();
    auto manifest_ptr = manifest.get();
    auto manifest_parser = std::make_unique<NiceMock<ManifestParserMock>>();
    auto manifest_parser_ptr = manifest_parser.get();
    auto yaml_parser = std::make_unique<NiceMock<YamlParserMock>>();
    auto yaml_parser_ptr = yaml_parser.get();
    auto input_parser = std::make_unique<NiceMock<InputParserMock>>();
    auto prototype_converter = std::make_unique<NiceMock<PrototypeInFileConverterMock>>();

    Parser parser(
        std::move(yaml_parser),
        std::move(input_parser),
        std::move(manifest_parser),
        std::move(prototype_converter));

    EXPECT_CALL(*yaml_parser_ptr, from_file(_)).WillOnce(Return(std::move(yaml_node)));
    EXPECT_CALL(*manifest_parser_ptr, parse(Ref(*yaml_node_ptr))).WillOnce(Return(std::move(manifest)));

    auto parsed_manifest = parser.parse_manifest("path");
    EXPECT_EQ(parsed_manifest.get(), manifest_ptr);
}

TEST(ParserTest, ParseInputPassesYamlNodeToInputParser) {
    auto yaml_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto yaml_node_ptr = yaml_node.get();
    auto manifest_parser = std::make_unique<NiceMock<ManifestParserMock>>();
    auto yaml_parser = std::make_unique<NiceMock<YamlParserMock>>();
    auto yaml_parser_ptr = yaml_parser.get();
    auto input_parser = std::make_unique<NiceMock<InputParserMock>>();
    auto input_parser_ptr = input_parser.get();
    auto input = std::make_unique<NiceMock<InputMock>>();
    auto input_ptr = input.get();
    auto prototype_converter = std::make_unique<NiceMock<PrototypeInFileConverterMock>>();

    Parser parser(
        std::move(yaml_parser),
        std::move(input_parser),
        std::move(manifest_parser),
        std::move(prototype_converter));

    EXPECT_CALL(*yaml_parser_ptr, from_file(_)).WillOnce(Return(std::move(yaml_node)));
    EXPECT_CALL(*input_parser_ptr, parse(Ref(*yaml_node_ptr))).WillOnce(Return(std::move(input)));

    auto parsed_input = parser.parse_input("path");
    EXPECT_EQ(parsed_input.get(), input_ptr);
}

TEST(ParserTest, ParseInputFromPrototypePassesYamlNodeToConverterAndThenToInputParser) {
    auto yaml_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto yaml_node_ptr = yaml_node.get();
    auto converted_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto converted_node_ptr = converted_node.get();
    auto manifest_parser = std::make_unique<NiceMock<ManifestParserMock>>();
    auto yaml_parser = std::make_unique<NiceMock<YamlParserMock>>();
    auto yaml_parser_ptr = yaml_parser.get();
    auto input_parser = std::make_unique<NiceMock<InputParserMock>>();
    auto input_parser_ptr = input_parser.get();
    auto input = std::make_unique<NiceMock<InputMock>>();
    auto input_ptr = input.get();
    auto prototype_converter = std::make_unique<NiceMock<PrototypeInFileConverterMock>>();
    auto prototype_converter_ptr = prototype_converter.get();

    Parser parser(
        std::move(yaml_parser),
        std::move(input_parser),
        std::move(manifest_parser),
        std::move(prototype_converter));

    EXPECT_CALL(*yaml_parser_ptr, from_file(_)).WillOnce(Return(std::move(yaml_node)));
    EXPECT_CALL(*prototype_converter_ptr, convert(Ref(*yaml_node_ptr))).WillOnce(Return(std::move(converted_node)));
    EXPECT_CALL(*input_parser_ptr, parse(Ref(*converted_node_ptr))).WillOnce(Return(std::move(input)));

    auto parsed_input = parser.parse_input_from_prototype("path");
    EXPECT_EQ(parsed_input.get(), input_ptr);
}

}