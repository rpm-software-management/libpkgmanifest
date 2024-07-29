#include "liblockfile/mocks/objects/lockfile/lockfilefactorymock.hpp"
#include "liblockfile/mocks/objects/lockfile/lockfileinternalmock.hpp"
#include "liblockfile/mocks/objects/packages/packagesinternalmock.hpp"
#include "liblockfile/mocks/objects/packages/packagesparsermock.hpp"
#include "liblockfile/mocks/objects/version/versioninternalmock.hpp"
#include "liblockfile/mocks/objects/version/versionparsermock.hpp"
#include "liblockfile/mocks/yaml/yamlnodemock.hpp"

#include "liblockfile/objects/lockfile/lockfileparser.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace liblockfile::internal;

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::NiceMock;
using ::testing::Pointer;
using ::testing::Ref;
using ::testing::Return;
using ::testing::Test;

class LockFileParserTest : public Test {
protected:
    virtual void SetUp() {
        auto file_wrapper = std::make_unique<NiceMock<LockFileInternalMock>>();
        file = file_wrapper.get();

        auto file_factory_wrapper = std::make_unique<NiceMock<LockFileFactoryMock>>();
        EXPECT_CALL(*file_factory_wrapper, create()).WillOnce(Return(std::move(file_wrapper)));

        auto packages_parser_wrapper = std::make_unique<NiceMock<PackagesParserMock>>();
        packages_parser = packages_parser_wrapper.get();

        auto version_parser_wrapper = std::make_unique<NiceMock<VersionParserMock>>();
        version_parser = version_parser_wrapper.get();

        EXPECT_CALL(yaml_node, get(_))
            .Times(AnyNumber())
            .WillRepeatedly([]() { return std::make_unique<NiceMock<YamlNodeMock>>(); });
        
        parser = std::make_unique<LockFileParser>(
            std::move(file_factory_wrapper), 
            std::move(packages_parser_wrapper), 
            std::move(version_parser_wrapper)
        );
    }

    NiceMock<LockFileInternalMock> * file;
    NiceMock<PackagesParserMock> * packages_parser;
    NiceMock<VersionParserMock> * version_parser;
    NiceMock<YamlNodeMock> yaml_node;

    std::unique_ptr<LockFileParser> parser;
};

TEST_F(LockFileParserTest, ParserSetsDocumentFromYamlNode) {
    auto document_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto document_node_ptr = document_node.get();
    
    EXPECT_CALL(yaml_node, get("document")).WillOnce(Return(std::move(document_node)));
    EXPECT_CALL(*document_node_ptr, as_string()).WillOnce(Return("id"));
    EXPECT_CALL(*file, set_document("id"));
    parser->parse(yaml_node);
}

TEST_F(LockFileParserTest, ParserSetsVersionFromVersionParser) {
    auto version_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto version_node_ptr = version_node.get();

    auto version = std::make_unique<NiceMock<VersionInternalMock>>();
    auto version_ptr = version.get();

    EXPECT_CALL(yaml_node, get("version")).WillOnce(Return(std::move(version_node)));
    EXPECT_CALL(*version_parser, parse(Ref(*version_node_ptr))).WillOnce(Return(std::move(version)));
    EXPECT_CALL(*file, set_version(Pointer(version_ptr)));
    parser->parse(yaml_node);
}

TEST_F(LockFileParserTest, ParserSetsPackagesFromPackagesParser) {
    auto data_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto data_node_ptr = data_node.get();
    auto packages_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto packages_node_ptr = packages_node.get();

    auto packages = std::make_unique<NiceMock<PackagesInternalMock>>();
    auto packages_ptr = packages.get();

    EXPECT_CALL(yaml_node, get("data")).WillOnce(Return(std::move(data_node)));
    EXPECT_CALL(*data_node_ptr, get("packages")).WillOnce(Return(std::move(packages_node)));
    EXPECT_CALL(*packages_parser, parse(Ref(*packages_node_ptr))).WillOnce(Return(std::move(packages)));
    EXPECT_CALL(*file, set_packages(Pointer(packages_ptr)));
    parser->parse(yaml_node);
}

TEST_F(LockFileParserTest, ParserReturnsTheObjectCreatedByFactory) {
    auto parsed_file = parser->parse(yaml_node);
    EXPECT_EQ(parsed_file.get(), file);
}

}