#include "libpkgmanifest/mocks/objects/checksum/checksummock.hpp"
#include "libpkgmanifest/mocks/objects/checksum/checksumparsermock.hpp"
#include "libpkgmanifest/mocks/objects/module/modulemock.hpp"
#include "libpkgmanifest/mocks/objects/module/moduleparsermock.hpp"
#include "libpkgmanifest/mocks/objects/package/packagefactorymock.hpp"
#include "libpkgmanifest/mocks/objects/package/packagemock.hpp"
#include "libpkgmanifest/mocks/yaml/yamlnodemock.hpp"

#include "libpkgmanifest/objects/package/packageparser.hpp"

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

class PackageParserTest : public Test {
protected:
    virtual void SetUp() {
        auto package = std::make_unique<NiceMock<PackageMock>>();
        package_ptr = package.get();

        auto package_factory_wrapper = std::make_shared<NiceMock<PackageFactoryMock>>();
        EXPECT_CALL(*package_factory_wrapper, create()).WillOnce(Return(std::move(package)));

        auto checksum_parser_wrapper = std::make_unique<NiceMock<ChecksumParserMock>>();
        checksum_parser = checksum_parser_wrapper.get();

        auto module_parser_wrapper = std::make_unique<NiceMock<ModuleParserMock>>();
        module_parser = module_parser_wrapper.get();

        EXPECT_CALL(yaml_node, get(_))
            .Times(AnyNumber())
            .WillRepeatedly([]() { return std::make_unique<NiceMock<YamlNodeMock>>(); });

        EXPECT_CALL(yaml_node, has(_)).Times(AnyNumber()).WillRepeatedly(Return(false));

        parser = std::make_unique<PackageParser>(
            std::move(checksum_parser_wrapper),
            std::move(module_parser_wrapper),
            package_factory_wrapper
        );
    }

    NiceMock<ChecksumParserMock> * checksum_parser;
    NiceMock<ModuleParserMock> * module_parser;
    NiceMock<PackageMock> * package_ptr;
    NiceMock<YamlNodeMock> yaml_node;

    std::unique_ptr<PackageParser> parser;
};

TEST_F(PackageParserTest, ParserSetsArchFromArgument) {
    EXPECT_CALL(*package_ptr, set_arch("x86_64"));
    parser->parse("x86_64", yaml_node);
}

TEST_F(PackageParserTest, ParserSetsRepoIdFromYamlNode) {
    auto repoid_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto repoid_node_ptr = repoid_node.get();
    
    EXPECT_CALL(yaml_node, has("repoid")).WillOnce(Return(true));
    EXPECT_CALL(yaml_node, get("repoid")).WillOnce(Return(std::move(repoid_node)));
    EXPECT_CALL(*repoid_node_ptr, as_string()).WillOnce(Return("id"));
    EXPECT_CALL(*package_ptr, set_repo_id("id"));
    parser->parse("arch", yaml_node);
}

TEST_F(PackageParserTest, ParserDoesNotSetRepoIdIfNotProvided) {
    EXPECT_CALL(yaml_node, has("repoid")).WillOnce(Return(false));
    EXPECT_CALL(yaml_node, get("repoid")).Times(0);
    EXPECT_CALL(*package_ptr, set_repo_id(_)).Times(0);
    parser->parse("arch", yaml_node);
}

TEST_F(PackageParserTest, ParserSetsUrlFromYamlNode) {
    auto url_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto url_node_ptr = url_node.get();
    
    EXPECT_CALL(yaml_node, has("url")).WillOnce(Return(true));
    EXPECT_CALL(yaml_node, get("url")).WillOnce(Return(std::move(url_node)));
    EXPECT_CALL(*url_node_ptr, as_string()).WillOnce(Return("url"));
    EXPECT_CALL(*package_ptr, set_url("url"));
    parser->parse("arch", yaml_node);
}

TEST_F(PackageParserTest, ParserDoesNotSetUrlIfNotProvided) {
    EXPECT_CALL(yaml_node, has("url")).WillOnce(Return(false));
    EXPECT_CALL(yaml_node, get("url")).Times(0);
    EXPECT_CALL(*package_ptr, set_url(_)).Times(0);
    parser->parse("arch", yaml_node);
}

TEST_F(PackageParserTest, ParserSetsChecksumFromChecksumParser) {
    auto checksum_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto checksum_node_ptr = checksum_node.get();
    auto checksum = std::make_unique<NiceMock<ChecksumMock>>();
    auto checksum_ptr = checksum.get();

    EXPECT_CALL(yaml_node, get("checksum")).WillOnce(Return(std::move(checksum_node)));
    EXPECT_CALL(*checksum_parser, parse(Ref(*checksum_node_ptr))).WillOnce(Return(std::move(checksum)));
    EXPECT_CALL(*package_ptr, set_checksum(Pointer(checksum_ptr)));
    parser->parse("arch", yaml_node);
}

TEST_F(PackageParserTest, ParserSetsSizeFromYamlNode) {
    auto size_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto size_node_ptr = size_node.get();
    
    EXPECT_CALL(yaml_node, get("size")).WillOnce(Return(std::move(size_node)));
    EXPECT_CALL(*size_node_ptr, as_uint64()).WillOnce(Return(6651234566512345));
    EXPECT_CALL(*package_ptr, set_size(6651234566512345));
    parser->parse("arch", yaml_node);
}

TEST_F(PackageParserTest, ParserSetsNevraFromYamlNode) {
    auto nevra_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto nevra_node_ptr = nevra_node.get();
    
    EXPECT_CALL(yaml_node, get("nevra")).WillOnce(Return(std::move(nevra_node)));
    EXPECT_CALL(*nevra_node_ptr, as_string()).WillOnce(Return("nevra"));
    EXPECT_CALL(*package_ptr, set_nevra("nevra"));
    parser->parse("arch", yaml_node);
}

TEST_F(PackageParserTest, ParserSetsSrpmFromYamlNode) {
    auto srpm_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto srpm_node_ptr = srpm_node.get();
    
    EXPECT_CALL(yaml_node, has("srpm")).WillOnce(Return(true));
    EXPECT_CALL(yaml_node, get("srpm")).WillOnce(Return(std::move(srpm_node)));
    EXPECT_CALL(*srpm_node_ptr, as_string()).WillOnce(Return("pkg-1.0.0"));
    EXPECT_CALL(*package_ptr, set_srpm("pkg-1.0.0"));
    parser->parse("arch", yaml_node);
}

TEST_F(PackageParserTest, ParserDoesNotSetSrpmIfNotProvided) {
    EXPECT_CALL(yaml_node, has("srpm")).WillOnce(Return(false));
    EXPECT_CALL(yaml_node, get("srpm")).Times(0);
    EXPECT_CALL(*package_ptr, set_srpm(_)).Times(0);
    parser->parse("arch", yaml_node);
}

TEST_F(PackageParserTest, ParserSetsModuleFromModuleParser) {
    auto module_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto module_node_ptr = module_node.get();
    auto module = std::make_unique<NiceMock<ModuleMock>>();
    auto module_ptr = module.get();

    EXPECT_CALL(yaml_node, has("module")).WillOnce(Return(true));
    EXPECT_CALL(yaml_node, get("module")).WillOnce(Return(std::move(module_node)));
    EXPECT_CALL(*module_parser, parse(Ref(*module_node_ptr))).WillOnce(Return(std::move(module)));
    EXPECT_CALL(*package_ptr, set_module(Pointer(module_ptr)));
    parser->parse("arch", yaml_node);
}

TEST_F(PackageParserTest, ParserDoesNotSetModuleIfNotProvided) {
    EXPECT_CALL(yaml_node, has("module")).WillOnce(Return(false));
    EXPECT_CALL(yaml_node, get("module")).Times(0);
    EXPECT_CALL(*package_ptr, set_module(_)).Times(0);
    parser->parse("arch", yaml_node);
}

TEST_F(PackageParserTest, ParserReturnsTheObjectCreatedByFactory) {
    auto parsed_package = parser->parse("arch", yaml_node);
    EXPECT_EQ(parsed_package.get(), package_ptr);
}

}