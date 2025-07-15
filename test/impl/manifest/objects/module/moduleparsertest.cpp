// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/manifest/mocks/objects/module/modulemock.hpp"
#include "impl/manifest/mocks/objects/module/modulefactorymock.hpp"
#include "impl/common/mocks/tools/stringsplittermock.hpp"
#include "impl/common/mocks/yaml/yamlnodemock.hpp"

#include "impl/manifest/objects/module/moduleparser.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal::manifest;

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::Test;

class ModuleParserTest : public Test {
protected:
    virtual void SetUp() {
        auto module = std::make_unique<NiceMock<ModuleMock>>();
        module_ptr = module.get();

        auto module_factory = std::make_shared<NiceMock<ModuleFactoryMock>>();
        EXPECT_CALL(*module_factory, create()).WillOnce(Return(std::move(module)));
    
        string_splitter = std::make_shared<NiceMock<StringSplitterMock>>();
        parser = std::make_unique<ModuleParser>(module_factory, string_splitter);
    }

    std::shared_ptr<NiceMock<StringSplitterMock>> string_splitter;

    NiceMock<ModuleMock> * module_ptr;
    NiceMock<YamlNodeMock> yaml_node;

    std::unique_ptr<ModuleParser> parser;
};

TEST_F(ModuleParserTest, ParserSetsNameFromYamlNode) {
    EXPECT_CALL(yaml_node, as_string()).WillOnce(Return("awesome-module:singlecarenotgiven"));
    EXPECT_CALL(*string_splitter, split("awesome-module:singlecarenotgiven", ':')).WillOnce(
        Return(std::vector<std::string>{"awesome-module", "singlecarenotgiven"})
    );
    EXPECT_CALL(*module_ptr, set_name("awesome-module"));
    parser->parse(yaml_node);
}

TEST_F(ModuleParserTest, ParserSetsStreamFromYamlNode) {
    EXPECT_CALL(yaml_node, as_string()).WillOnce(Return("notcaringmodule:66.6"));
    EXPECT_CALL(*string_splitter, split("notcaringmodule:66.6", ':')).WillOnce(
        Return(std::vector<std::string>{"notcaringmodule", "66.6"})
    );
    EXPECT_CALL(*module_ptr, set_stream("66.6"));
    parser->parse(yaml_node);
}

TEST_F(ModuleParserTest, ParserReturnsTheObjectCreatedByFactory) {
    EXPECT_CALL(*string_splitter, split(_, _)).WillOnce(
        Return(std::vector<std::string>{"madmodule", "steamystreamy"})
    );

    auto parsed_module = parser->parse(yaml_node);
    EXPECT_EQ(parsed_module.get(), module_ptr);
}

}