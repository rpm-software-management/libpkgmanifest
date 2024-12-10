#include "impl/input/mocks/objects/modules/modulesmock.hpp"
#include "impl/input/mocks/objects/modules/modulesfactorymock.hpp"
#include "impl/common/mocks/operations/stringlistparsermock.hpp"
#include "impl/common/mocks/yaml/yamlnodemock.hpp"

#include "impl/input/objects/modules/modulesparser.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal::input;

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::ReturnPointee;
using ::testing::Test;

class InputModulesParserTest : public Test {
protected:
    virtual void SetUp() {
        auto modules = std::make_unique<NiceMock<ModulesMock>>();
        modules_ptr = modules.get();

        auto modules_factory = std::make_shared<NiceMock<ModulesFactoryMock>>();
        EXPECT_CALL(*modules_factory, create()).WillOnce(Return(std::move(modules)));

        string_list_parser = std::make_shared<NiceMock<StringListParserMock>>();

        EXPECT_CALL(yaml_node, get(_))
            .Times(AnyNumber())
            .WillRepeatedly([]() { return std::make_unique<NiceMock<YamlNodeMock>>(); });

        EXPECT_CALL(yaml_node, has(_)).Times(AnyNumber()).WillRepeatedly(Return(false));
    
        parser = std::make_unique<ModulesParser>(modules_factory, string_list_parser);
    }

    NiceMock<ModulesMock> * modules_ptr;
    NiceMock<YamlNodeMock> yaml_node;
    std::shared_ptr<NiceMock<StringListParserMock>> string_list_parser;

    std::unique_ptr<ModulesParser> parser;
};

TEST_F(InputModulesParserTest, ParserSetsEnableModulesFromStringListParser) {
    auto enables_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto enables_node_ptr = enables_node.get();

    std::vector<std::string> target_enable_modules;
    std::vector<std::string> source_enable_modules{"module1", "module2"};

    EXPECT_CALL(*modules_ptr, get_enables()).WillRepeatedly(ReturnPointee(&target_enable_modules));
    EXPECT_CALL(yaml_node, has("enable")).WillOnce(Return(true));
    EXPECT_CALL(yaml_node, get("enable")).WillOnce(Return(std::move(enables_node)));
    EXPECT_CALL(*string_list_parser, parse(Ref(*enables_node_ptr))).WillOnce(Return(source_enable_modules));
    auto modules = parser->parse(yaml_node);

    EXPECT_EQ(source_enable_modules, modules->get_enables());
}

TEST_F(InputModulesParserTest, ParserSetsDisableModulesFromStringListParser) {
    auto disables_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto disables_node_ptr = disables_node.get();

    std::vector<std::string> target_disable_modules;
    std::vector<std::string> source_disable_modules{"some_module_1", "other_module_2"};

    EXPECT_CALL(*modules_ptr, get_disables()).WillRepeatedly(ReturnPointee(&target_disable_modules));
    EXPECT_CALL(yaml_node, has("disable")).WillOnce(Return(true));
    EXPECT_CALL(yaml_node, get("disable")).WillOnce(Return(std::move(disables_node)));
    EXPECT_CALL(*string_list_parser, parse(Ref(*disables_node_ptr))).WillOnce(Return(source_disable_modules));
    auto modules = parser->parse(yaml_node);

    EXPECT_EQ(source_disable_modules, modules->get_disables());
}

TEST_F(InputModulesParserTest, ParserReturnsTheObjectCreatedByFactory) {
    auto parsed_modules = parser->parse(yaml_node);
    EXPECT_EQ(parsed_modules.get(), modules_ptr);
}

}