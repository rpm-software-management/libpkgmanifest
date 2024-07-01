#include "liblockfile/mocks/objects/checksum/checksuminternalmock.hpp"
#include "liblockfile/mocks/objects/checksum/checksumparsermock.hpp"
#include "liblockfile/mocks/objects/package/packagefactorymock.hpp"
#include "liblockfile/mocks/objects/package/packageinternalmock.hpp"
#include "liblockfile/mocks/yaml/yamlnodemock.hpp"

#include "liblockfile/objects/package/packageparser.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace liblockfile;

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
        auto package = std::make_unique<NiceMock<PackageInternalMock>>();
        package_ptr = package.get();

        EXPECT_CALL(package_factory, create()).WillOnce(Return(std::move(package)));

        EXPECT_CALL(yaml_node, get(_))
            .Times(AnyNumber())
            .WillRepeatedly([]() { return std::make_unique<NiceMock<YamlNodeMock>>(); });
    }

    NiceMock<ChecksumParserMock> checksum_parser;
    NiceMock<PackageFactoryMock> package_factory;
    NiceMock<PackageInternalMock> * package_ptr;
    NiceMock<YamlNodeMock> yaml_node;

    PackageParser parser{checksum_parser, package_factory};
};

TEST_F(PackageParserTest, ParserSetsArchFromArgument) {
    EXPECT_CALL(*package_ptr, set_arch("x86_64"));
    parser.parse("x86_64", yaml_node);
}

TEST_F(PackageParserTest, ParserSetsRepoIdFromYamlNode) {
    auto repoid_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto repoid_node_ptr = repoid_node.get();
    ON_CALL(*repoid_node, as_string()).WillByDefault(Return("id"));
    
    EXPECT_CALL(yaml_node, get("repoid")).WillOnce(Return(std::move(repoid_node)));
    EXPECT_CALL(*repoid_node_ptr, as_string());
    EXPECT_CALL(*package_ptr, set_repo_id("id"));
    parser.parse("arch", yaml_node);
}

TEST_F(PackageParserTest, ParserSetsChecksumFromChecksumParser) {
    auto checksum_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto checksum_node_ptr = checksum_node.get();
    auto checksum = std::make_unique<NiceMock<ChecksumInternalMock>>();
    auto checksum_ptr = checksum.get();

    EXPECT_CALL(yaml_node, get("checksum")).WillOnce(Return(std::move(checksum_node)));
    EXPECT_CALL(checksum_parser, parse(Ref(*checksum_node_ptr))).WillOnce(Return(std::move(checksum)));
    EXPECT_CALL(*package_ptr, set_checksum(Pointer(checksum_ptr)));
    parser.parse("arch", yaml_node);
}

TEST_F(PackageParserTest, ParserSetsSizeFromYamlNode) {
    auto size_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto size_node_ptr = size_node.get();
    ON_CALL(*size_node, as_uint64()).WillByDefault(Return(6651234566512345));
    
    EXPECT_CALL(yaml_node, get("size")).WillOnce(Return(std::move(size_node)));
    EXPECT_CALL(*size_node_ptr, as_uint64());
    EXPECT_CALL(*package_ptr, set_size(6651234566512345));
    parser.parse("arch", yaml_node);
}

TEST_F(PackageParserTest, ParserSetsNevraFromYamlNode) {
    auto nevra_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto nevra_node_ptr = nevra_node.get();
    ON_CALL(*nevra_node, as_string()).WillByDefault(Return("nevra"));
    
    EXPECT_CALL(yaml_node, get("nevra")).WillOnce(Return(std::move(nevra_node)));
    EXPECT_CALL(*nevra_node_ptr, as_string());
    EXPECT_CALL(*package_ptr, set_nevra("nevra"));
    parser.parse("arch", yaml_node);
}

TEST_F(PackageParserTest, ParserSetsSrpmFromYamlNode) {
    auto srpm_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto srpm_node_ptr = srpm_node.get();
    ON_CALL(*srpm_node, as_string()).WillByDefault(Return("pkg-1.0.0"));
    
    EXPECT_CALL(yaml_node, get("srpm")).WillOnce(Return(std::move(srpm_node)));
    EXPECT_CALL(*srpm_node_ptr, as_string());
    EXPECT_CALL(*package_ptr, set_srpm("pkg-1.0.0"));
    parser.parse("arch", yaml_node);
}

TEST_F(PackageParserTest, ParserReturnsTheObjectCreatedByFactory) {
    auto parsed_package = parser.parse("arch", yaml_node);
    EXPECT_EQ(parsed_package.get(), package_ptr);
}

}