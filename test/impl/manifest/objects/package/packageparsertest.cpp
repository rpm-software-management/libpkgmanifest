#include "impl/manifest/mocks/objects/checksum/checksummock.hpp"
#include "impl/manifest/mocks/objects/checksum/checksumparsermock.hpp"
#include "impl/manifest/mocks/objects/module/modulemock.hpp"
#include "impl/manifest/mocks/objects/module/moduleparsermock.hpp"
#include "impl/manifest/mocks/objects/nevra/nevramock.hpp"
#include "impl/manifest/mocks/objects/nevra/nevraparsermock.hpp"
#include "impl/manifest/mocks/objects/package/packagefactorymock.hpp"
#include "impl/manifest/mocks/objects/package/packagemock.hpp"
#include "impl/common/mocks/yaml/yamlnodemock.hpp"

#include "impl/common/yaml/yamlnode.hpp"
#include "impl/manifest/objects/package/packageparser.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal::manifest;

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::ElementsAre;
using ::testing::NiceMock;
using ::testing::Pointer;
using ::testing::Ref;
using ::testing::Return;
using ::testing::ReturnPointee;
using ::testing::Test;
using ::testing::Throw;

class PackageParserTest : public Test {
protected:
    virtual void SetUp() {
        auto package = std::make_unique<NiceMock<PackageMock>>();
        package_ptr = package.get();

        auto package_factory_wrapper = std::make_shared<NiceMock<PackageFactoryMock>>();
        EXPECT_CALL(*package_factory_wrapper, create()).WillOnce(Return(std::move(package)));

        auto checksum_parser_wrapper = std::make_unique<NiceMock<ChecksumParserMock>>();
        checksum_parser = checksum_parser_wrapper.get();

        auto nevra_parser_wrapper = std::make_unique<NiceMock<NevraParserMock>>();
        nevra_parser = nevra_parser_wrapper.get();

        auto module_parser_wrapper = std::make_unique<NiceMock<ModuleParserMock>>();
        module_parser = module_parser_wrapper.get();

        EXPECT_CALL(yaml_node, get(_))
            .Times(AnyNumber())
            .WillRepeatedly([]() { return std::make_unique<NiceMock<YamlNodeMock>>(); });

        EXPECT_CALL(yaml_node, has(_)).Times(AnyNumber()).WillRepeatedly(Return(false));

        parser = std::make_unique<PackageParser>(
            std::move(checksum_parser_wrapper),
            std::move(nevra_parser_wrapper),
            std::move(module_parser_wrapper),
            package_factory_wrapper
        );
    }

    NiceMock<ChecksumParserMock> * checksum_parser;
    NiceMock<NevraParserMock> * nevra_parser;
    NiceMock<ModuleParserMock> * module_parser;
    NiceMock<PackageMock> * package_ptr;
    NiceMock<YamlNodeMock> yaml_node;

    std::unique_ptr<PackageParser> parser;
};

TEST_F(PackageParserTest, ParserSetsRepoIdFromYamlNode) {
    auto repoid_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto repoid_node_ptr = repoid_node.get();
    
    EXPECT_CALL(yaml_node, get("repo_id")).WillOnce(Return(std::move(repoid_node)));
    EXPECT_CALL(*repoid_node_ptr, as_string()).WillOnce(Return("id"));
    EXPECT_CALL(*package_ptr, set_repo_id("id"));
    parser->parse("arch", yaml_node);
}

TEST_F(PackageParserTest, ParserSetsLocationFromYamlNode) {
    auto location_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto location_node_ptr = location_node.get();
    
    EXPECT_CALL(yaml_node, has("location")).WillOnce(Return(true));
    EXPECT_CALL(yaml_node, get("location")).WillOnce(Return(std::move(location_node)));
    EXPECT_CALL(*location_node_ptr, as_string()).WillOnce(Return("path"));
    EXPECT_CALL(*package_ptr, set_location("path"));
    parser->parse("arch", yaml_node);
}

TEST_F(PackageParserTest, ParserDoesNotSetLocationIfNotProvided) {
    EXPECT_CALL(yaml_node, has("location")).WillOnce(Return(false));
    EXPECT_CALL(yaml_node, get("location")).Times(0);
    EXPECT_CALL(*package_ptr, set_location(_)).Times(0);
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

TEST_F(PackageParserTest, ParserAddsParentArchsFromYamlNode) {
    std::vector<std::string> archs;
    EXPECT_CALL(*package_ptr, get_parent_archs()).WillRepeatedly(ReturnPointee(&archs));

    auto node = std::make_unique<NiceMock<YamlNodeMock>>();

    std::vector<std::unique_ptr<IYamlNode>> arch_nodes; 
    auto arch1_node = std::make_unique<NiceMock<YamlNodeMock>>();
    EXPECT_CALL(*arch1_node, as_string()).WillOnce(Return("x86_64"));
    auto arch2_node = std::make_unique<NiceMock<YamlNodeMock>>();
    EXPECT_CALL(*arch2_node, as_string()).WillOnce(Return("i686"));
    arch_nodes.push_back(std::move(arch1_node));
    arch_nodes.push_back(std::move(arch2_node));

    EXPECT_CALL(*node, as_list()).WillOnce(Return(std::move(arch_nodes)));

    EXPECT_CALL(yaml_node, has("parent_archs")).WillOnce(Return(true));
    EXPECT_CALL(yaml_node, get("parent_archs")).WillOnce(Return(std::move(node)));
    parser->parse("arch", yaml_node);
    EXPECT_THAT(archs, ElementsAre("x86_64", "i686"));
}

TEST_F(PackageParserTest, ParserDoesNotAddParentArchsIfNotProvided) {
    EXPECT_CALL(yaml_node, has("parent_archs")).WillOnce(Return(false));
    EXPECT_CALL(yaml_node, get("parent_archs")).Times(0);
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

TEST_F(PackageParserTest, ParserSetsNevraFromNevraParserAndNameArchFields) {
    auto evr_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto evr_node_ptr = evr_node.get();
    auto name_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto name_node_ptr = name_node.get();
    auto nevra = std::make_unique<NiceMock<NevraMock>>();
    auto nevra_ptr = nevra.get();

    EXPECT_CALL(yaml_node, get("evr")).WillOnce(Return(std::move(evr_node)));
    EXPECT_CALL(yaml_node, get("name")).WillOnce(Return(std::move(name_node)));
    EXPECT_CALL(*name_node_ptr, as_string()).WillOnce(Return("pkg"));
    EXPECT_CALL(*nevra_parser, parse("pkg", "x86_64", Ref(*evr_node_ptr))).WillOnce(Return(std::move(nevra)));
    EXPECT_CALL(*package_ptr, set_nevra(Pointer(nevra_ptr)));
    parser->parse("x86_64", yaml_node);
}

TEST_F(PackageParserTest, ParserSetsSrpmFromNevraParser) {
    auto srpm_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto srpm_node_ptr = srpm_node.get();
    auto srpm = std::make_unique<NiceMock<NevraMock>>();
    auto srpm_ptr = srpm.get();

    EXPECT_CALL(yaml_node, has("srpm")).WillOnce(Return(true));
    EXPECT_CALL(yaml_node, get("srpm")).WillOnce(Return(std::move(srpm_node)));
    EXPECT_CALL(*nevra_parser, parse(Ref(*srpm_node_ptr))).WillOnce(Return(std::move(srpm)));
    EXPECT_CALL(*package_ptr, set_srpm(Pointer(srpm_ptr)));
    parser->parse("arch", yaml_node);
}

TEST_F(PackageParserTest, ParserDoesNotSetSrpmIfNotProvided) {
    EXPECT_CALL(yaml_node, has("srpm")).WillOnce(Return(false));
    EXPECT_CALL(yaml_node, get("srpm")).Times(0);
    EXPECT_CALL(*package_ptr, set_srpm(_)).Times(0);
    parser->parse("arch", yaml_node);
}

TEST_F(PackageParserTest, ParserThrowsAnExceptionIfSizeHasInvalidFormat) {
    auto size_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto size_node_ptr = size_node.get();
    
    EXPECT_CALL(yaml_node, get("size")).WillOnce(Return(std::move(size_node)));
    EXPECT_CALL(*size_node_ptr, as_uint64()).WillOnce(Throw(YamlInvalidValueConversionError("error")));
    EXPECT_THROW(parser->parse("arch", yaml_node), PackageSizeFormatError);
}

TEST_F(PackageParserTest, ParserReturnsTheObjectCreatedByFactory) {
    auto parsed_package = parser->parse("arch", yaml_node);
    EXPECT_EQ(parsed_package.get(), package_ptr);
}

}