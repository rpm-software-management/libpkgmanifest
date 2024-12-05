#include "impl/manifest/mocks/objects/nevra/nevramock.hpp"
#include "impl/manifest/mocks/objects/nevra/nevrafactorymock.hpp"
#include "impl/common/mocks/yaml/yamlnodemock.hpp"

#include "impl/manifest/objects/nevra/nevraparser.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal::manifest;

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::Test;

class NevraParserTest : public Test {
protected:
    virtual void SetUp() {
        auto nevra = std::make_unique<NiceMock<NevraMock>>();
        nevra_ptr = nevra.get();

        auto nevra_factory = std::make_shared<NiceMock<NevraFactoryMock>>();
        EXPECT_CALL(*nevra_factory, create()).WillOnce(Return(std::move(nevra)));
    
        parser = std::make_unique<NevraParser>(nevra_factory);
    }

    NiceMock<NevraMock> * nevra_ptr;
    NiceMock<YamlNodeMock> yaml_node;

    std::unique_ptr<NevraParser> parser;
};

TEST_F(NevraParserTest, ParserSetsTheArchitectureFromYamlNode) {
    EXPECT_CALL(yaml_node, as_string()).WillOnce(Return("pkg-1.0.0-1.rel1.arch"));
    EXPECT_CALL(*nevra_ptr, set_arch("arch"));
    parser->parse(yaml_node);
}

TEST_F(NevraParserTest, ParserThrowsAnExceptionWhenArchitectureIsMissingInTheString) {
    EXPECT_CALL(yaml_node, as_string()).WillOnce(Return("pkg-1"));
    EXPECT_THROW(parser->parse(yaml_node), NevraParseError);
}

TEST_F(NevraParserTest, ParserSetsTheReleaseFromYamlNode) {
    EXPECT_CALL(yaml_node, as_string()).WillOnce(Return("pkg-1.0.0-1.rel1.arch"));
    EXPECT_CALL(*nevra_ptr, set_release("1.rel1"));
    parser->parse(yaml_node);
}

TEST_F(NevraParserTest, ParserThrowsAnExceptionWhenReleaseIsMissingInTheString) {
    EXPECT_CALL(yaml_node, as_string()).WillOnce(Return("pkg.arch"));
    EXPECT_THROW(parser->parse(yaml_node), NevraParseError);
}

TEST_F(NevraParserTest, ParserSetsTheVersionFromYamlNode) {
    EXPECT_CALL(yaml_node, as_string()).WillOnce(Return("pkg-1.0.0-1.rel1.arch"));
    EXPECT_CALL(*nevra_ptr, set_version("1.0.0"));
    parser->parse(yaml_node);
}

TEST_F(NevraParserTest, ParserSetsTheVersionFromYamlNodeWhenEpochIsPresent) {
    EXPECT_CALL(yaml_node, as_string()).WillOnce(Return("pkg-5:1.0.0-1.rel1.arch"));
    EXPECT_CALL(*nevra_ptr, set_version("1.0.0"));
    parser->parse(yaml_node);
}

TEST_F(NevraParserTest, ParserThrowsAnExceptionWhenVersionIsMissingInTheString) {
    EXPECT_CALL(yaml_node, as_string()).WillOnce(Return("pkg-2.rel2.arch"));
    EXPECT_THROW(parser->parse(yaml_node), NevraParseError);
}

TEST_F(NevraParserTest, ParserSetsTheEpochFromYamlNode) {
    EXPECT_CALL(yaml_node, as_string()).WillOnce(Return("pkg-3:1.0.0-1.rel1.arch"));
    EXPECT_CALL(*nevra_ptr, set_epoch("3"));
    parser->parse(yaml_node);
}

TEST_F(NevraParserTest, ParserDoesNotSetTheEpochWhenItIsMissingInTheString) {
    EXPECT_CALL(yaml_node, as_string()).WillOnce(Return("pkg-1.0.0-1.rel1.arch"));
    EXPECT_CALL(*nevra_ptr, set_epoch("_")).Times(0);
    parser->parse(yaml_node);
}

TEST_F(NevraParserTest, ParserSetsTheNameFromYamlNode) {
    EXPECT_CALL(yaml_node, as_string()).WillOnce(Return("pkg-1.0.0-1.rel1.arch"));
    EXPECT_CALL(*nevra_ptr, set_name("pkg"));
    parser->parse(yaml_node);
}

TEST_F(NevraParserTest, ParserSetsTheNameFromYamlNodeWhenContainingDashes) {
    EXPECT_CALL(yaml_node, as_string()).WillOnce(Return("pkg-name-1.0.0-1.rel1.arch"));
    EXPECT_CALL(*nevra_ptr, set_name("pkg-name"));
    parser->parse(yaml_node);
}

TEST_F(NevraParserTest, EvrParserSetsNameFromArgument) {
    EXPECT_CALL(yaml_node, as_string()).WillOnce(Return("1.1.1-1.rel"));
    EXPECT_CALL(*nevra_ptr, set_name("package"));
    parser->parse("package", "arch", yaml_node);
}

TEST_F(NevraParserTest, EvrParserSetsArchFromArgument) {
    EXPECT_CALL(yaml_node, as_string()).WillOnce(Return("1.1.1-1.rel"));
    EXPECT_CALL(*nevra_ptr, set_arch("i686"));
    parser->parse("name", "i686", yaml_node);
}

TEST_F(NevraParserTest, EvrParserSetsTheReleaseFromYamlNode) {
    EXPECT_CALL(yaml_node, as_string()).WillOnce(Return("1.2.3-4.rel5"));
    EXPECT_CALL(*nevra_ptr, set_release("4.rel5"));
    parser->parse("name", "arch", yaml_node);
}

TEST_F(NevraParserTest, EvrParserThrowsAnExceptionWhenReleaseIsMissingInTheString) {
    EXPECT_CALL(yaml_node, as_string()).WillOnce(Return("1.2.3"));
    EXPECT_THROW(parser->parse("name", "arch", yaml_node), NevraParseError);
}

TEST_F(NevraParserTest, EvrParserSetsTheVersionFromYamlNode) {
    EXPECT_CALL(yaml_node, as_string()).WillOnce(Return("9.8.7-1.rel2"));
    EXPECT_CALL(*nevra_ptr, set_version("9.8.7"));
    parser->parse("name", "arch", yaml_node);
}

TEST_F(NevraParserTest, EvrParserSetsTheVersionFromYamlNodeWhenEpochIsPresent) {
    EXPECT_CALL(yaml_node, as_string()).WillOnce(Return("3:4.5.6-2.rel3"));
    EXPECT_CALL(*nevra_ptr, set_version("4.5.6"));
    parser->parse("name", "arch", yaml_node);
}

TEST_F(NevraParserTest, EvrParserSetsTheEpochFromYamlNode) {
    EXPECT_CALL(yaml_node, as_string()).WillOnce(Return("3:1.0.0-1.rel1"));
    EXPECT_CALL(*nevra_ptr, set_epoch("3"));
    parser->parse("name", "arch", yaml_node);
}

TEST_F(NevraParserTest, EvrParserDoesNotSetTheEpochWhenItIsMissingInTheString) {
    EXPECT_CALL(yaml_node, as_string()).WillOnce(Return("1.0.0-1.rel1"));
    EXPECT_CALL(*nevra_ptr, set_epoch("_")).Times(0);
    parser->parse("name", "arch", yaml_node);
}

TEST_F(NevraParserTest, ParserReturnsTheObjectCreatedByFactory) {
    EXPECT_CALL(yaml_node, as_string()).WillOnce(Return("pkg-1.0-1.rel1"));
    auto parsed_nevra = parser->parse(yaml_node);
    EXPECT_EQ(parsed_nevra.get(), nevra_ptr);
}

TEST_F(NevraParserTest, EvrParserReturnsTheObjectCreatedByFactory) {
    EXPECT_CALL(yaml_node, as_string()).WillOnce(Return("1.0-1.rel1"));
    auto parsed_nevra = parser->parse("name", "arch", yaml_node);
    EXPECT_EQ(parsed_nevra.get(), nevra_ptr);
}

}