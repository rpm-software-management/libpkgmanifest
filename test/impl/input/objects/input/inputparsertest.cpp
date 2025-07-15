// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/common/mocks/objects/repositories/repositoriesmock.hpp"
#include "impl/common/mocks/objects/repositories/repositoriesparsermock.hpp"
#include "impl/common/mocks/objects/version/versionmock.hpp"
#include "impl/common/mocks/objects/version/versionparsermock.hpp"
#include "impl/common/mocks/operations/stringlistparsermock.hpp"
#include "impl/common/mocks/yaml/yamlnodemock.hpp"
#include "impl/input/mocks/objects/input/inputfactorymock.hpp"
#include "impl/input/mocks/objects/input/inputmock.hpp"
#include "impl/input/mocks/objects/modules/modulesmock.hpp"
#include "impl/input/mocks/objects/modules/modulesparsermock.hpp"
#include "impl/input/mocks/objects/options/optionsmock.hpp"
#include "impl/input/mocks/objects/options/optionsparsermock.hpp"
#include "impl/input/mocks/objects/packages/packagesmock.hpp"
#include "impl/input/mocks/objects/packages/packagesparsermock.hpp"

#include "impl/input/objects/input/inputparser.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal::input;

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::ElementsAre;
using ::testing::NiceMock;
using ::testing::Pointer;
using ::testing::Ref;
using ::testing::Return;
using ::testing::ReturnPointee;
using ::testing::Test;

class InputParserTest : public Test {
protected:
    virtual void SetUp() {
        auto input_wrapper = std::make_unique<NiceMock<InputMock>>();
        input = input_wrapper.get();

        auto input_factory_wrapper = std::make_unique<NiceMock<InputFactoryMock>>();
        EXPECT_CALL(*input_factory_wrapper, create()).WillOnce(Return(std::move(input_wrapper)));

        auto repositories_parser_wrapper = std::make_unique<NiceMock<RepositoriesParserMock>>();
        repositories_parser = repositories_parser_wrapper.get();

        auto version_parser_wrapper = std::make_unique<NiceMock<VersionParserMock>>();
        version_parser = version_parser_wrapper.get();

        auto packages_parser_wrapper = std::make_unique<NiceMock<PackagesParserMock>>();
        packages_parser = packages_parser_wrapper.get();

        auto modules_parser_wrapper = std::make_unique<NiceMock<ModulesParserMock>>();
        modules_parser = modules_parser_wrapper.get();

        auto options_parser_wrapper = std::make_unique<NiceMock<OptionsParserMock>>();
        options_parser = options_parser_wrapper.get();

        auto string_list_parser_wrapper = std::make_unique<NiceMock<StringListParserMock>>();
        string_list_parser = string_list_parser_wrapper.get();

        EXPECT_CALL(yaml_node, get(_))
            .Times(AnyNumber())
            .WillRepeatedly([]() { return std::make_unique<NiceMock<YamlNodeMock>>(); });

        EXPECT_CALL(yaml_node, has(_)).Times(AnyNumber()).WillRepeatedly(Return(false));
        
        EXPECT_CALL(*repositories_parser, parse(_))
            .Times(AnyNumber())
            .WillRepeatedly([]() { return std::make_unique<NiceMock<RepositoriesMock>>(); });

        parser = std::make_unique<InputParser>(
            std::move(input_factory_wrapper),
            std::move(repositories_parser_wrapper),
            std::move(version_parser_wrapper),
            std::move(packages_parser_wrapper),
            std::move(modules_parser_wrapper),
            std::move(options_parser_wrapper),
            std::move(string_list_parser_wrapper)
        );
    }

    NiceMock<InputMock> * input;
    NiceMock<RepositoriesParserMock> * repositories_parser;
    NiceMock<VersionParserMock> * version_parser;
    NiceMock<PackagesParserMock> * packages_parser;
    NiceMock<ModulesParserMock> * modules_parser;
    NiceMock<OptionsParserMock> * options_parser;
    NiceMock<StringListParserMock> * string_list_parser;
    NiceMock<RepositoriesMock> repositories;
    NiceMock<YamlNodeMock> yaml_node;

    std::unique_ptr<InputParser> parser;
};

TEST_F(InputParserTest, ParserSetsDocumentFromYamlNode) {
    auto document_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto document_node_ptr = document_node.get();
    
    EXPECT_CALL(yaml_node, get("document")).WillOnce(Return(std::move(document_node)));
    EXPECT_CALL(*document_node_ptr, as_string()).WillOnce(Return("id"));
    EXPECT_CALL(*input, set_document("id"));
    parser->parse(yaml_node);
}

TEST_F(InputParserTest, ParserSetsVersionFromVersionParser) {
    auto version_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto version_node_ptr = version_node.get();

    auto version = std::make_unique<NiceMock<VersionMock>>();
    auto version_ptr = version.get();

    EXPECT_CALL(yaml_node, get("version")).WillOnce(Return(std::move(version_node)));
    EXPECT_CALL(*version_parser, parse(Ref(*version_node_ptr))).WillOnce(Return(std::move(version)));
    EXPECT_CALL(*input, set_version(Pointer(version_ptr)));
    parser->parse(yaml_node);
}

TEST_F(InputParserTest, ParserSetsRepositoriesFromRepositoriesParser) {
    auto repositories_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto repositories_node_ptr = repositories_node.get();

    auto repositories = std::make_unique<NiceMock<RepositoriesMock>>();
    auto repositories_ptr = repositories.get();

    EXPECT_CALL(yaml_node, get("repositories")).WillOnce(Return(std::move(repositories_node)));
    EXPECT_CALL(*repositories_parser, parse(Ref(*repositories_node_ptr))).WillOnce(Return(std::move(repositories)));
    EXPECT_CALL(*input, set_repositories(Pointer(repositories_ptr)));
    parser->parse(yaml_node);
}

TEST_F(InputParserTest, ParserSetsPackagesFromPackagesParser) {
    auto packages_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto packages_node_ptr = packages_node.get();

    auto packages = std::make_unique<NiceMock<PackagesMock>>();
    auto packages_ptr = packages.get();

    EXPECT_CALL(yaml_node, get("packages")).WillOnce(Return(std::move(packages_node)));
    EXPECT_CALL(*packages_parser, parse(Ref(*packages_node_ptr))).WillOnce(Return(std::move(packages)));
    EXPECT_CALL(*input, set_packages(Pointer(packages_ptr)));
    parser->parse(yaml_node);
}

TEST_F(InputParserTest, ParserSetsModulesFromModulesParser) {
    auto modules_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto modules_node_ptr = modules_node.get();

    auto modules = std::make_unique<NiceMock<ModulesMock>>();
    auto modules_ptr = modules.get();

    EXPECT_CALL(yaml_node, has("modules")).WillOnce(Return(true));
    EXPECT_CALL(yaml_node, get("modules")).WillOnce(Return(std::move(modules_node)));
    EXPECT_CALL(*modules_parser, parse(Ref(*modules_node_ptr))).WillOnce(Return(std::move(modules)));
    EXPECT_CALL(*input, set_modules(Pointer(modules_ptr)));
    parser->parse(yaml_node);
}

TEST_F(InputParserTest, ParserSetsOptionsFromOptionsParser) {
    auto options_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto options_node_ptr = options_node.get();

    auto options = std::make_unique<NiceMock<OptionsMock>>();
    auto options_ptr = options.get();

    EXPECT_CALL(yaml_node, has("options")).WillOnce(Return(true));
    EXPECT_CALL(yaml_node, get("options")).WillOnce(Return(std::move(options_node)));
    EXPECT_CALL(*options_parser, parse(Ref(*options_node_ptr))).WillOnce(Return(std::move(options)));
    EXPECT_CALL(*input, set_options(Pointer(options_ptr)));
    parser->parse(yaml_node);
}

TEST_F(InputParserTest, ParserAddsArchsFromYamlNode) {
    std::vector<std::string> archs;
    EXPECT_CALL(*input, get_archs()).WillRepeatedly(ReturnPointee(&archs));

    auto node = std::make_unique<NiceMock<YamlNodeMock>>();

    std::vector<std::unique_ptr<IYamlNode>> arch_nodes; 
    auto arch1_node = std::make_unique<NiceMock<YamlNodeMock>>();
    EXPECT_CALL(*arch1_node, as_string()).WillOnce(Return("x86_64"));
    auto arch2_node = std::make_unique<NiceMock<YamlNodeMock>>();
    EXPECT_CALL(*arch2_node, as_string()).WillOnce(Return("i686"));
    auto arch3_node = std::make_unique<NiceMock<YamlNodeMock>>();
    EXPECT_CALL(*arch3_node, as_string()).WillOnce(Return("src"));
    arch_nodes.push_back(std::move(arch1_node));
    arch_nodes.push_back(std::move(arch2_node));
    arch_nodes.push_back(std::move(arch3_node));

    EXPECT_CALL(*node, as_list()).WillOnce(Return(std::move(arch_nodes)));

    EXPECT_CALL(yaml_node, get("archs")).WillOnce(Return(std::move(node)));
    parser->parse(yaml_node);
    EXPECT_THAT(archs, ElementsAre("x86_64", "i686", "src"));
}

TEST_F(InputParserTest, ParserReturnsTheObjectCreatedByFactory) {
    auto parsed_input = parser->parse(yaml_node);
    EXPECT_EQ(parsed_input.get(), input);
}

}