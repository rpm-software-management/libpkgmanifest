#include "libpkgmanifest/mocks/objects/package/packagemock.hpp"
#include "libpkgmanifest/mocks/objects/package/packageparsermock.hpp"
#include "libpkgmanifest/mocks/objects/packages/packagesfactorymock.hpp"
#include "libpkgmanifest/mocks/objects/packages/packagesmock.hpp"
#include "libpkgmanifest/mocks/yaml/yamlnodemock.hpp"

#include "libpkgmanifest/objects/packages/packagesparser.hpp"

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
using ::testing::ReturnPointee;
using ::testing::Test;

class PackagesParserTest : public Test {
protected:
    virtual void SetUp() {
        auto packages = std::make_unique<NiceMock<PackagesMock>>();
        packages_ptr = packages.get();

        auto packages_factory_wrapper = std::make_shared<NiceMock<PackagesFactoryMock>>();
        EXPECT_CALL(*packages_factory_wrapper, create()).WillOnce(Return(std::move(packages)));

        auto package_parser_wrapper = std::make_unique<NiceMock<PackageParserMock>>();
        package_parser = package_parser_wrapper.get();

        parser = std::make_unique<PackagesParser>(
            std::move(package_parser_wrapper),
            packages_factory_wrapper
        );
    }

    NiceMock<PackageParserMock> * package_parser;
    NiceMock<PackagesMock> * packages_ptr;
    NiceMock<YamlNodeMock> yaml_node;

    std::unique_ptr<PackagesParser> parser;
};

TEST_F(PackagesParserTest, ParserAddsAllPackagesForEachArchInYamlNode) {
    auto aarch64_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto aarch64_node_ptr = aarch64_node.get();
    auto aarch64_pkg1_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto aarch64_pkg1_node_ptr = aarch64_pkg1_node.get();
    auto aarch64_pkg2_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto aarch64_pkg2_node_ptr = aarch64_pkg2_node.get();
    auto aarch64_pkg1 = std::make_unique<NiceMock<PackageMock>>();
    auto aarch64_pkg1_ptr = aarch64_pkg1.get();
    auto aarch64_pkg2 = std::make_unique<NiceMock<PackageMock>>();
    auto aarch64_pkg2_ptr = aarch64_pkg2.get();

    auto i686_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto i686_node_ptr = i686_node.get();
    auto i686_pkg1_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto i686_pkg1_node_ptr = i686_pkg1_node.get();
    auto i686_pkg2_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto i686_pkg2_node_ptr = i686_pkg2_node.get();
    auto i686_pkg1 = std::make_unique<NiceMock<PackageMock>>();
    auto i686_pkg1_ptr = i686_pkg1.get();
    auto i686_pkg2 = std::make_unique<NiceMock<PackageMock>>();
    auto i686_pkg2_ptr = i686_pkg2.get();

    std::vector<std::unique_ptr<IYamlNode>> aarch64_package_nodes;
    aarch64_package_nodes.push_back(std::move(aarch64_pkg1_node));
    aarch64_package_nodes.push_back(std::move(aarch64_pkg2_node));

    std::vector<std::unique_ptr<IYamlNode>> i686_package_nodes;
    i686_package_nodes.push_back(std::move(i686_pkg1_node));
    i686_package_nodes.push_back(std::move(i686_pkg2_node));

    std::map<std::string, std::unique_ptr<IYamlNode>> nodes_map;
    nodes_map.insert({"aarch64", std::move(aarch64_node)});
    nodes_map.insert({"i686", std::move(i686_node)});

    EXPECT_CALL(yaml_node, as_map()).WillOnce(Return(std::move(nodes_map)));
    EXPECT_CALL(*aarch64_node_ptr, as_list()).WillOnce(Return(std::move(aarch64_package_nodes)));
    EXPECT_CALL(*i686_node_ptr, as_list()).WillOnce(Return(std::move(i686_package_nodes)));

    EXPECT_CALL(*package_parser, parse("aarch64", Ref(*aarch64_pkg1_node_ptr))).WillOnce(Return(std::move(aarch64_pkg1)));
    EXPECT_CALL(*package_parser, parse("aarch64", Ref(*aarch64_pkg2_node_ptr))).WillOnce(Return(std::move(aarch64_pkg2)));
    EXPECT_CALL(*package_parser, parse("i686", Ref(*i686_pkg1_node_ptr))).WillOnce(Return(std::move(i686_pkg1)));
    EXPECT_CALL(*package_parser, parse("i686", Ref(*i686_pkg2_node_ptr))).WillOnce(Return(std::move(i686_pkg2)));

    EXPECT_CALL(*packages_ptr, add(Pointer(aarch64_pkg1_ptr)));
    EXPECT_CALL(*packages_ptr, add(Pointer(aarch64_pkg2_ptr)));
    EXPECT_CALL(*packages_ptr, add(Pointer(i686_pkg1_ptr)));
    EXPECT_CALL(*packages_ptr, add(Pointer(i686_pkg2_ptr)));

    parser->parse(yaml_node);
}

TEST_F(PackagesParserTest, ParserReturnsTheObjectCreatedByFactory) {
    auto parsed_packages = parser->parse(yaml_node);
    EXPECT_EQ(parsed_packages.get(), packages_ptr);
}

}