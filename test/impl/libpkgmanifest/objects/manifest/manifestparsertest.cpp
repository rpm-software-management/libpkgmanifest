#include "libpkgmanifest/mocks/objects/manifest/manifestfactorymock.hpp"
#include "libpkgmanifest/mocks/objects/manifest/manifestmock.hpp"
#include "libpkgmanifest/mocks/objects/packages/packagesmock.hpp"
#include "libpkgmanifest/mocks/objects/packages/packagesparsermock.hpp"
#include "libpkgmanifest/mocks/objects/version/versionmock.hpp"
#include "libpkgmanifest/mocks/objects/version/versionparsermock.hpp"
#include "libpkgmanifest/mocks/yaml/yamlnodemock.hpp"

#include "libpkgmanifest/objects/manifest/manifestparser.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal;

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::NiceMock;
using ::testing::Pointer;
using ::testing::Ref;
using ::testing::Return;
using ::testing::Test;

class ManifestParserTest : public Test {
protected:
    virtual void SetUp() {
        auto manifest_wrapper = std::make_unique<NiceMock<ManifestMock>>();
        manifest = manifest_wrapper.get();

        auto manifest_factory_wrapper = std::make_unique<NiceMock<ManifestFactoryMock>>();
        EXPECT_CALL(*manifest_factory_wrapper, create()).WillOnce(Return(std::move(manifest_wrapper)));

        auto packages_parser_wrapper = std::make_unique<NiceMock<PackagesParserMock>>();
        packages_parser = packages_parser_wrapper.get();

        auto version_parser_wrapper = std::make_unique<NiceMock<VersionParserMock>>();
        version_parser = version_parser_wrapper.get();

        EXPECT_CALL(yaml_node, get(_))
            .Times(AnyNumber())
            .WillRepeatedly([]() { return std::make_unique<NiceMock<YamlNodeMock>>(); });
        
        parser = std::make_unique<ManifestParser>(
            std::move(manifest_factory_wrapper), 
            std::move(packages_parser_wrapper), 
            std::move(version_parser_wrapper)
        );
    }

    NiceMock<ManifestMock> * manifest;
    NiceMock<PackagesParserMock> * packages_parser;
    NiceMock<VersionParserMock> * version_parser;
    NiceMock<YamlNodeMock> yaml_node;

    std::unique_ptr<ManifestParser> parser;
};

TEST_F(ManifestParserTest, ParserSetsDocumentFromYamlNode) {
    auto document_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto document_node_ptr = document_node.get();
    
    EXPECT_CALL(yaml_node, get("document")).WillOnce(Return(std::move(document_node)));
    EXPECT_CALL(*document_node_ptr, as_string()).WillOnce(Return("id"));
    EXPECT_CALL(*manifest, set_document("id"));
    parser->parse(yaml_node);
}

TEST_F(ManifestParserTest, ParserSetsVersionFromVersionParser) {
    auto version_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto version_node_ptr = version_node.get();

    auto version = std::make_unique<NiceMock<VersionMock>>();
    auto version_ptr = version.get();

    EXPECT_CALL(yaml_node, get("version")).WillOnce(Return(std::move(version_node)));
    EXPECT_CALL(*version_parser, parse(Ref(*version_node_ptr))).WillOnce(Return(std::move(version)));
    EXPECT_CALL(*manifest, set_version(Pointer(version_ptr)));
    parser->parse(yaml_node);
}

TEST_F(ManifestParserTest, ParserSetsPackagesFromPackagesParser) {
    auto data_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto data_node_ptr = data_node.get();
    auto packages_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto packages_node_ptr = packages_node.get();

    auto packages = std::make_unique<NiceMock<PackagesMock>>();
    auto packages_ptr = packages.get();

    EXPECT_CALL(yaml_node, get("data")).WillOnce(Return(std::move(data_node)));
    EXPECT_CALL(*data_node_ptr, get("packages")).WillOnce(Return(std::move(packages_node)));
    EXPECT_CALL(*packages_parser, parse(Ref(*packages_node_ptr))).WillOnce(Return(std::move(packages)));
    EXPECT_CALL(*manifest, set_packages(Pointer(packages_ptr)));
    parser->parse(yaml_node);
}

TEST_F(ManifestParserTest, ParserReturnsTheObjectCreatedByFactory) {
    auto parsed_manifest = parser->parse(yaml_node);
    EXPECT_EQ(parsed_manifest.get(), manifest);
}

}