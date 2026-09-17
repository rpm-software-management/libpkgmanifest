// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/common/mocks/objects/repositories/repositoriesmock.hpp"
#include "impl/common/mocks/objects/repositories/repositoriesparsermock.hpp"
#include "impl/common/mocks/yaml/yamlnodemock.hpp"
#include "impl/manifest/mocks/objects/manifest/manifestfactorymock.hpp"
#include "impl/manifest/mocks/objects/manifest/manifestmock.hpp"
#include "impl/manifest/mocks/objects/packages/packagesmock.hpp"
#include "impl/manifest/mocks/objects/packages/packagesparsermock.hpp"
#include "impl/manifest/mocks/operations/packagerepositorybindermock.hpp"
#include "impl/manifest/objects/manifest/manifestfactory.hpp"
#include "impl/manifest/objects/manifest/manifestparser.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal::manifest;

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::AtMost;
using ::testing::Matcher;
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
        EXPECT_CALL(*manifest_factory_wrapper, create()).Times(AtMost(1)).WillOnce(Return(std::move(manifest_wrapper)));

        auto packages_parser_wrapper = std::make_unique<NiceMock<PackagesParserMock>>();
        packages_parser = packages_parser_wrapper.get();

        auto repositories_parser_wrapper = std::make_unique<NiceMock<RepositoriesParserMock>>();
        repositories_parser = repositories_parser_wrapper.get();

        EXPECT_CALL(yaml_node, get(_)).Times(AnyNumber()).WillRepeatedly([]() {
            return std::make_unique<NiceMock<YamlNodeMock>>();
        });

        auto document_node_wrapper = std::make_unique<NiceMock<YamlNodeMock>>();
        document_node = document_node_wrapper.get();
        ON_CALL(*document_node, as_string()).WillByDefault(Return(MANIFEST_DOCUMENT_ID));
        EXPECT_CALL(yaml_node, get("document")).WillOnce(Return(std::move(document_node_wrapper)));

        auto version_node_wrapper = std::make_unique<NiceMock<YamlNodeMock>>();
        version_node = version_node_wrapper.get();
        ON_CALL(*version_node, as_string()).WillByDefault(Return(manifest_document_version_string()));
        EXPECT_CALL(yaml_node, get("version")).Times(AtMost(1)).WillOnce(Return(std::move(version_node_wrapper)));

        auto data_node_wrapper = std::make_unique<NiceMock<YamlNodeMock>>();
        data_node = data_node_wrapper.get();

        EXPECT_CALL(yaml_node, get("data")).Times(AtMost(1)).WillOnce(Return(std::move(data_node_wrapper)));

        EXPECT_CALL(*data_node, get(_)).Times(AnyNumber()).WillRepeatedly([]() {
            return std::make_unique<NiceMock<YamlNodeMock>>();
        });

        EXPECT_CALL(*packages_parser, parse(_)).Times(AnyNumber()).WillRepeatedly([]() {
            return std::make_unique<NiceMock<PackagesMock>>();
        });

        EXPECT_CALL(*repositories_parser, parse(_)).Times(AnyNumber()).WillRepeatedly([]() {
            return std::make_unique<NiceMock<RepositoriesMock>>();
        });

        binder = std::make_shared<NiceMock<PackageRepositoryBinderMock>>();

        parser = std::make_unique<ManifestParser>(
            std::move(manifest_factory_wrapper),
            std::move(packages_parser_wrapper),
            std::move(repositories_parser_wrapper),
            binder);
    }

    NiceMock<ManifestMock> * manifest;
    NiceMock<PackagesParserMock> * packages_parser;
    NiceMock<RepositoriesParserMock> * repositories_parser;
    std::shared_ptr<NiceMock<PackageRepositoryBinderMock>> binder;
    NiceMock<RepositoriesMock> repositories;
    NiceMock<YamlNodeMock> yaml_node;
    NiceMock<YamlNodeMock> * document_node;
    NiceMock<YamlNodeMock> * version_node;
    NiceMock<YamlNodeMock> * data_node;

    std::unique_ptr<ManifestParser> parser;
};

TEST_F(ManifestParserTest, ParserRejectsWrongDocument) {
    EXPECT_CALL(*document_node, as_string()).WillOnce(Return("wrong-document"));
    EXPECT_THROW(parser->parse(yaml_node), std::runtime_error);
}

TEST_F(ManifestParserTest, ParserRejectsUnsupportedVersion) {
    EXPECT_CALL(*version_node, as_string()).WillOnce(Return("0.0.1"));
    EXPECT_THROW(parser->parse(yaml_node), std::runtime_error);
}

TEST_F(ManifestParserTest, ParserSetsPackagesFromPackagesParser) {
    auto packages_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto packages_node_ptr = packages_node.get();

    auto packages = std::make_unique<NiceMock<PackagesMock>>();
    auto packages_ptr = packages.get();

    EXPECT_CALL(*data_node, get("packages")).WillOnce(Return(std::move(packages_node)));
    EXPECT_CALL(*packages_parser, parse(Ref(*packages_node_ptr))).WillOnce(Return(std::move(packages)));
    EXPECT_CALL(*manifest, set_packages(Pointer(packages_ptr)));
    parser->parse(yaml_node);
}

TEST_F(ManifestParserTest, ParserSetsRepositoriesFromRepositoriesParser) {
    auto repositories_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto repositories_node_ptr = repositories_node.get();

    auto repositories = std::make_unique<NiceMock<RepositoriesMock>>();
    auto repositories_ptr = repositories.get();

    EXPECT_CALL(*data_node, get("repositories")).WillOnce(Return(std::move(repositories_node)));
    EXPECT_CALL(*repositories_parser, parse(Ref(*repositories_node_ptr))).WillOnce(Return(std::move(repositories)));
    EXPECT_CALL(*manifest, set_repositories(Pointer(repositories_ptr)));
    parser->parse(yaml_node);
}

TEST_F(ManifestParserTest, RepositoriesAreAttachedThroughBinderToPackagesAfterTheyAreParsed) {
    auto packages_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto packages_node_ptr = packages_node.get();

    auto packages = std::make_unique<NiceMock<PackagesMock>>();
    auto packages_ptr = packages.get();

    auto repositories_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto repositories_node_ptr = repositories_node.get();

    auto repositories = std::make_unique<NiceMock<RepositoriesMock>>();
    auto repositories_ptr = repositories.get();

    EXPECT_CALL(*data_node, get("packages")).WillOnce(Return(std::move(packages_node)));
    EXPECT_CALL(*data_node, get("repositories")).WillOnce(Return(std::move(repositories_node)));
    EXPECT_CALL(*packages_parser, parse(Ref(*packages_node_ptr))).WillOnce(Return(std::move(packages)));
    EXPECT_CALL(*repositories_parser, parse(Ref(*repositories_node_ptr))).WillOnce(Return(std::move(repositories)));
    EXPECT_CALL(*binder, bind(Ref(*repositories_ptr), Matcher<IPackages &>(Ref(*packages_ptr))));
    parser->parse(yaml_node);
}

TEST_F(ManifestParserTest, ParserReturnsTheObjectCreatedByFactory) {
    auto parsed_manifest = parser->parse(yaml_node);
    EXPECT_EQ(parsed_manifest.get(), manifest);
}

}  // namespace
