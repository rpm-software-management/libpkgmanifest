#include "impl/common/mocks/yaml/yamlnodemock.hpp"
#include "impl/input/mocks/objects/options/optionsfactorymock.hpp"
#include "impl/input/mocks/objects/options/optionsmock.hpp"

#include "impl/input/objects/options/optionsparser.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal::input;

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::Test;

class InputOptionsParserTest : public Test {
protected:
    virtual void SetUp() {
        auto options = std::make_unique<NiceMock<OptionsMock>>();
        options_ptr = options.get();

        auto options_factory_wrapper = std::make_shared<NiceMock<OptionsFactoryMock>>();
        EXPECT_CALL(*options_factory_wrapper, create()).WillOnce(Return(std::move(options)));

        EXPECT_CALL(yaml_node, get(_))
            .Times(AnyNumber())
            .WillRepeatedly([]() { return std::make_unique<NiceMock<YamlNodeMock>>(); });
        
        parser = std::make_unique<OptionsParser>(options_factory_wrapper);
    }

    NiceMock<OptionsMock> * options_ptr;
    NiceMock<YamlNodeMock> yaml_node;

    std::unique_ptr<OptionsParser> parser;
};

TEST_F(InputOptionsParserTest, ParseSetsAllowErasingValue) {
    auto allow_erasing_node = std::make_unique<NiceMock<YamlNodeMock>>();
    EXPECT_CALL(*allow_erasing_node, as_bool()).WillOnce(Return(true));

    EXPECT_CALL(yaml_node, has("allow_erasing")).WillOnce(Return(true));
    EXPECT_CALL(yaml_node, get("allow_erasing")).WillOnce(Return(std::move(allow_erasing_node)));

    EXPECT_CALL(*options_ptr, set_allow_erasing(true));
    parser->parse(yaml_node);
}

TEST_F(InputOptionsParserTest, ParserReturnsTheObjectCreatedByFactory) {
    auto parsed_options = parser->parse(yaml_node);
    EXPECT_EQ(parsed_options.get(), options_ptr);
}

}