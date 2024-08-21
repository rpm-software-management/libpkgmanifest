#include "libpkgmanifest/mocks/objects/manifest/manifestmock.hpp"
#include "libpkgmanifest/mocks/objects/manifest/manifestparsermock.hpp"
#include "libpkgmanifest/mocks/yaml/yamlnodemock.hpp"
#include "libpkgmanifest/mocks/yaml/yamlparsermock.hpp"

#include "libpkgmanifest/operations/parser.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal;

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Return;

TEST(ParserTest, NodeFromYamlParserIsPassedToManifestParser) {
    auto yaml_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto yaml_node_ptr = yaml_node.get();
    auto manifest = std::make_unique<NiceMock<ManifestMock>>();
    auto manifest_ptr = manifest.get();
    auto manifest_parser = std::make_unique<NiceMock<ManifestParserMock>>();
    auto manifest_parser_ptr = manifest_parser.get();
    auto yaml_parser = std::make_unique<NiceMock<YamlParserMock>>();
    auto yaml_parser_ptr = yaml_parser.get();

    Parser parser(std::move(yaml_parser), std::move(manifest_parser));

    EXPECT_CALL(*yaml_parser_ptr, from_file(_)).WillOnce(Return(std::move(yaml_node)));
    EXPECT_CALL(*manifest_parser_ptr, parse(Ref(*yaml_node_ptr))).WillOnce(Return(std::move(manifest)));

    auto parsed_manifest = parser.parse("path");
    EXPECT_EQ(parsed_manifest.get(), manifest_ptr);
}

}