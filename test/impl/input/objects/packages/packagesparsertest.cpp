#include "impl/input/mocks/objects/packages/packagesmock.hpp"
#include "impl/input/mocks/objects/packages/packagesfactorymock.hpp"
#include "impl/common/mocks/operations/stringlistparsermock.hpp"
#include "impl/common/mocks/yaml/yamlnodemock.hpp"

#include "impl/input/objects/packages/packagesparser.hpp"

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

class InputPackagesParserTest : public Test {
protected:
    virtual void SetUp() {
        auto packages = std::make_unique<NiceMock<PackagesMock>>();
        packages_ptr = packages.get();

        EXPECT_CALL(*packages, get_installs()).WillRepeatedly(ReturnPointee(&empty_vector));

        auto packages_factory = std::make_shared<NiceMock<PackagesFactoryMock>>();
        EXPECT_CALL(*packages_factory, create()).WillOnce(Return(std::move(packages)));

        string_list_parser = std::make_shared<NiceMock<StringListParserMock>>();

        EXPECT_CALL(*string_list_parser, parse(_)).WillRepeatedly(Return(empty_vector));

        EXPECT_CALL(yaml_node, get(_))
            .Times(AnyNumber())
            .WillRepeatedly([]() { return std::make_unique<NiceMock<YamlNodeMock>>(); });

        EXPECT_CALL(yaml_node, has(_)).Times(AnyNumber()).WillRepeatedly(Return(false));
    
        parser = std::make_unique<PackagesParser>(packages_factory, string_list_parser);
    }

    NiceMock<PackagesMock> * packages_ptr;
    NiceMock<YamlNodeMock> yaml_node;
    std::shared_ptr<NiceMock<StringListParserMock>> string_list_parser;
    std::vector<std::string> empty_vector;

    std::unique_ptr<PackagesParser> parser;
};

TEST_F(InputPackagesParserTest, ParserSetsInstallPackagesFromStringListParser) {
    auto installs_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto installs_node_ptr = installs_node.get();

    std::vector<std::string> target_install_packages;
    std::vector<std::string> source_install_packages{"pkg1", "pkg2", "pkg3"};

    EXPECT_CALL(*packages_ptr, get_installs()).WillRepeatedly(ReturnPointee(&target_install_packages));
    EXPECT_CALL(yaml_node, get("install")).WillOnce(Return(std::move(installs_node)));
    EXPECT_CALL(*string_list_parser, parse(Ref(*installs_node_ptr))).WillOnce(Return(source_install_packages));
    auto packages = parser->parse(yaml_node);

    EXPECT_EQ(source_install_packages, packages->get_installs());
}

TEST_F(InputPackagesParserTest, ParserSetsReinstallPackagesFromStringListParser) {
    auto reinstalls_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto reinstalls_node_ptr = reinstalls_node.get();

    std::vector<std::string> target_reinstall_packages;
    std::vector<std::string> source_reinstall_packages{"pkgA", "pkgB", "pkgC", "pkgD"};

    EXPECT_CALL(*packages_ptr, get_reinstalls()).WillRepeatedly(ReturnPointee(&target_reinstall_packages));
    EXPECT_CALL(yaml_node, has("reinstall")).WillOnce(Return(true));
    EXPECT_CALL(yaml_node, get("reinstall")).WillOnce(Return(std::move(reinstalls_node)));
    EXPECT_CALL(*string_list_parser, parse(Ref(*reinstalls_node_ptr))).WillOnce(Return(source_reinstall_packages));
    auto packages = parser->parse(yaml_node);

    EXPECT_EQ(source_reinstall_packages, packages->get_reinstalls());
}

TEST_F(InputPackagesParserTest, ParserReturnsTheObjectCreatedByFactory) {
    auto parsed_packages = parser->parse(yaml_node);
    EXPECT_EQ(parsed_packages.get(), packages_ptr);
}

}