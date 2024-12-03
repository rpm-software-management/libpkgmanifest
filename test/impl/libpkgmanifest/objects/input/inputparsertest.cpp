#include "impl/libpkgmanifest/mocks/objects/input/inputfactorymock.hpp"
#include "impl/libpkgmanifest/mocks/objects/input/inputmock.hpp"
#include "impl/libpkgmanifest/mocks/objects/repositories/repositoriesmock.hpp"
#include "impl/libpkgmanifest/mocks/objects/repositories/repositoriesparsermock.hpp"
#include "impl/libpkgmanifest/mocks/objects/version/versionmock.hpp"
#include "impl/libpkgmanifest/mocks/objects/version/versionparsermock.hpp"
#include "impl/libpkgmanifest/mocks/yaml/yamlnodemock.hpp"

#include "impl/libpkgmanifest/objects/input/inputparser.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal;

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

        EXPECT_CALL(yaml_node, get(_))
            .Times(AnyNumber())
            .WillRepeatedly([]() { return std::make_unique<NiceMock<YamlNodeMock>>(); });
        
        EXPECT_CALL(*repositories_parser, parse(_))
            .Times(AnyNumber())
            .WillRepeatedly([]() { return std::make_unique<NiceMock<RepositoriesMock>>(); });

        parser = std::make_unique<InputParser>(
            std::move(input_factory_wrapper),
            std::move(repositories_parser_wrapper),
            std::move(version_parser_wrapper)
        );
    }

    NiceMock<InputMock> * input;
    NiceMock<RepositoriesParserMock> * repositories_parser;
    NiceMock<VersionParserMock> * version_parser;
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

TEST_F(InputParserTest, ParserAddsInstallPackagesFromYamlNode) {
    std::map<std::string, std::vector<std::string>> packages;
    EXPECT_CALL(*input, get_packages()).WillRepeatedly(ReturnPointee(&packages));

    auto node = std::make_unique<NiceMock<YamlNodeMock>>();

    std::map<std::string, std::unique_ptr<IYamlNode>> package_map_node;
    std::vector<std::unique_ptr<IYamlNode>> package_nodes; 
    auto package1_node = std::make_unique<NiceMock<YamlNodeMock>>();
    EXPECT_CALL(*package1_node, as_string()).WillOnce(Return("pkg1"));
    auto package2_node = std::make_unique<NiceMock<YamlNodeMock>>();
    EXPECT_CALL(*package2_node, as_string()).WillOnce(Return("pkg2"));
    package_nodes.push_back(std::move(package1_node));
    package_nodes.push_back(std::move(package2_node));

    auto inner_map_node = std::make_unique<NiceMock<YamlNodeMock>>();
    EXPECT_CALL(*inner_map_node, as_list()).WillOnce(Return(std::move(package_nodes)));
    package_map_node["install"] = std::move(inner_map_node);

    EXPECT_CALL(*node, as_map()).WillOnce(Return(std::move(package_map_node)));

    EXPECT_CALL(yaml_node, get("packages")).WillOnce(Return(std::move(node)));
    parser->parse(yaml_node);
    EXPECT_THAT(packages["install"], ElementsAre("pkg1", "pkg2"));
}

TEST_F(InputParserTest, ParserAddsReinstallPackagesFromYamlNode) {
    std::map<std::string, std::vector<std::string>> packages;
    EXPECT_CALL(*input, get_packages()).WillRepeatedly(ReturnPointee(&packages));

    auto node = std::make_unique<NiceMock<YamlNodeMock>>();

    std::map<std::string, std::unique_ptr<IYamlNode>> package_map_node;
    std::vector<std::unique_ptr<IYamlNode>> package_nodes; 
    auto package1_node = std::make_unique<NiceMock<YamlNodeMock>>();
    EXPECT_CALL(*package1_node, as_string()).WillOnce(Return("package1"));
    auto package2_node = std::make_unique<NiceMock<YamlNodeMock>>();
    EXPECT_CALL(*package2_node, as_string()).WillOnce(Return("package2"));
    package_nodes.push_back(std::move(package1_node));
    package_nodes.push_back(std::move(package2_node));

    auto inner_map_node = std::make_unique<NiceMock<YamlNodeMock>>();
    EXPECT_CALL(*inner_map_node, as_list()).WillOnce(Return(std::move(package_nodes)));
    package_map_node["reinstall"] = std::move(inner_map_node);

    EXPECT_CALL(*node, as_map()).WillOnce(Return(std::move(package_map_node)));

    EXPECT_CALL(yaml_node, get("packages")).WillOnce(Return(std::move(node)));
    parser->parse(yaml_node);
    EXPECT_THAT(packages["reinstall"], ElementsAre("package1", "package2"));
}

TEST_F(InputParserTest, ParserAddsEnableModulesFromYamlNode) {
    std::map<std::string, std::vector<std::string>> modules;
    EXPECT_CALL(*input, get_modules()).WillRepeatedly(ReturnPointee(&modules));

    auto node = std::make_unique<NiceMock<YamlNodeMock>>();

    std::map<std::string, std::unique_ptr<IYamlNode>> module_map_node;
    std::vector<std::unique_ptr<IYamlNode>> module_nodes; 
    auto module1_node = std::make_unique<NiceMock<YamlNodeMock>>();
    EXPECT_CALL(*module1_node, as_string()).WillOnce(Return("mod1"));
    auto module2_node = std::make_unique<NiceMock<YamlNodeMock>>();
    EXPECT_CALL(*module2_node, as_string()).WillOnce(Return("mod2"));
    module_nodes.push_back(std::move(module1_node));
    module_nodes.push_back(std::move(module2_node));

    auto inner_map_node = std::make_unique<NiceMock<YamlNodeMock>>();
    EXPECT_CALL(*inner_map_node, as_list()).WillOnce(Return(std::move(module_nodes)));
    module_map_node["enable"] = std::move(inner_map_node);

    EXPECT_CALL(*node, as_map()).WillOnce(Return(std::move(module_map_node)));

    EXPECT_CALL(yaml_node, get("modules")).WillOnce(Return(std::move(node)));
    parser->parse(yaml_node);
    EXPECT_THAT(modules["enable"], ElementsAre("mod1", "mod2"));
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