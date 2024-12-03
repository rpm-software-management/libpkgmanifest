#include "impl/libpkgmanifest/mocks/yaml/yamlnodefactorymock.hpp"
#include "impl/libpkgmanifest/mocks/yaml/yamlnodeinternalstub.hpp"

#include "impl/libpkgmanifest/operations/prototypeinfileconverter.hpp"

#include <format>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal;

using ::testing::NiceMock;
using ::testing::Return;
using ::testing::Test;

class PrototypeInFileConverterTest : public Test {
protected:
    virtual void SetUp() {
        auto node_factory = std::make_shared<NiceMock<YamlNodeFactoryMock>>();
        EXPECT_CALL(*node_factory, create())
            .WillRepeatedly([]() { 
                return std::make_unique<YamlNodeInternalStub>(); 
            });
        
        converter = std::make_unique<PrototypeInFileConverter>(node_factory);
    }

    std::unique_ptr<PrototypeInFileConverter> converter;
};

TEST_F(PrototypeInFileConverterTest, ConverterConvertsTheNodeToTheExpectedInputFormat) {
    YamlNodeInternalStub prototype_node;

    auto content_origin_node = std::make_unique<YamlNodeInternalStub>();

    auto repos_node = std::make_unique<YamlNodeInternalStub>();

    auto repo1_node = std::make_unique<YamlNodeInternalStub>();
    auto repo1_repoid_node = std::make_unique<YamlNodeInternalStub>();
    repo1_repoid_node->set("repo1");
    auto repo1_baseurl_node = std::make_unique<YamlNodeInternalStub>();
    repo1_baseurl_node->set("baseurl1");
    repo1_node->insert("repoid", std::move(repo1_repoid_node));
    repo1_node->insert("baseurl", std::move(repo1_baseurl_node));

    auto repo2_node = std::make_unique<YamlNodeInternalStub>();
    auto repo2_repoid_node = std::make_unique<YamlNodeInternalStub>();
    repo2_repoid_node->set("repo2");
    auto repo2_baseurl_node = std::make_unique<YamlNodeInternalStub>();
    repo2_baseurl_node->set("baseurl2");
    repo2_node->insert("repoid", std::move(repo2_repoid_node));
    repo2_node->insert("baseurl", std::move(repo2_baseurl_node));

    repos_node->add(std::move(repo1_node));
    repos_node->add(std::move(repo2_node));

    auto packages_node = std::make_unique<YamlNodeInternalStub>();
    auto package1_node = std::make_unique<YamlNodeInternalStub>();
    package1_node->set("pkg1");
    auto package2_node = std::make_unique<YamlNodeInternalStub>();
    package2_node->set("pkg2");

    // this node is expected to be ignored
    auto complex_pkg_node = std::make_unique<YamlNodeInternalStub>();
    auto complex_pkg_name_node = std::make_unique<YamlNodeInternalStub>();
    complex_pkg_name_node->set("pkg3");
    auto complex_pkg_arch_node = std::make_unique<YamlNodeInternalStub>();
    complex_pkg_name_node->set("arch_only");
    complex_pkg_node->insert("name", std::move(complex_pkg_name_node));
    complex_pkg_node->insert("arches", std::move(complex_pkg_arch_node));

    packages_node->add(std::move(package1_node));
    packages_node->add(std::move(package2_node));
    packages_node->add(std::move(complex_pkg_node));

    auto reinstall_packages_node = std::make_unique<YamlNodeInternalStub>();
    auto reinstall_package1_node = std::make_unique<YamlNodeInternalStub>();
    reinstall_package1_node->set("pkgA");
    auto reinstall_package2_node = std::make_unique<YamlNodeInternalStub>();
    reinstall_package2_node->set("pkgB");

    reinstall_packages_node->add(std::move(reinstall_package1_node));
    reinstall_packages_node->add(std::move(reinstall_package2_node));

    auto enable_modules_node = std::make_unique<YamlNodeInternalStub>();
    auto enable_module1_node = std::make_unique<YamlNodeInternalStub>();
    enable_module1_node->set("module1");
    auto enable_module2_node = std::make_unique<YamlNodeInternalStub>();
    enable_module2_node->set("module2");

    enable_modules_node->add(std::move(enable_module1_node));
    enable_modules_node->add(std::move(enable_module2_node));

    auto arches_node = std::make_unique<YamlNodeInternalStub>();
    auto arch1_node = std::make_unique<YamlNodeInternalStub>();
    arch1_node->set("arch1");
    auto arch2_node = std::make_unique<YamlNodeInternalStub>();
    arch2_node->set("arch2");

    arches_node->add(std::move(arch1_node));
    arches_node->add(std::move(arch2_node));

    auto allowerasing_node = std::make_unique<YamlNodeInternalStub>();
    allowerasing_node->set(true);

    content_origin_node->insert("repos", std::move(repos_node));
    prototype_node.insert("contentOrigin", std::move(content_origin_node));
    prototype_node.insert("packages", std::move(packages_node));
    prototype_node.insert("reinstallPackages", std::move(reinstall_packages_node));
    prototype_node.insert("moduleEnable", std::move(enable_modules_node));
    prototype_node.insert("arches", std::move(arches_node));
    prototype_node.insert("allowerasing", std::move(allowerasing_node));

    auto node = converter->convert(prototype_node);
    EXPECT_EQ(INPUT_PROTOTYPE_DOCUMENT_ID, node->get("document")->as_string());
    EXPECT_EQ(std::format("{}.{}.{}", 
        INPUT_PROTOTYPE_DOCUMENT_VERSION_MAJOR,
        INPUT_PROTOTYPE_DOCUMENT_VERSION_MINOR,
        INPUT_PROTOTYPE_DOCUMENT_VERSION_PATCH), node->get("version")->as_string());
    EXPECT_EQ("repo1", node->get("repositories")->as_list()[0]->get("id")->as_string());
    EXPECT_EQ("baseurl1", node->get("repositories")->as_list()[0]->get("baseurl")->as_string());
    EXPECT_EQ("repo2", node->get("repositories")->as_list()[1]->get("id")->as_string());
    EXPECT_EQ("baseurl2", node->get("repositories")->as_list()[1]->get("baseurl")->as_string());
    EXPECT_EQ(2, node->get("packages")->as_map().size());
    EXPECT_EQ(2, node->get("packages")->as_map()["install"]->as_list().size());
    EXPECT_EQ("pkg1", node->get("packages")->as_map()["install"]->as_list()[0]->as_string());
    EXPECT_EQ("pkg2", node->get("packages")->as_map()["install"]->as_list()[1]->as_string());
    EXPECT_EQ(2, node->get("packages")->as_map()["reinstall"]->as_list().size());
    EXPECT_EQ("pkgA", node->get("packages")->as_map()["reinstall"]->as_list()[0]->as_string());
    EXPECT_EQ("pkgB", node->get("packages")->as_map()["reinstall"]->as_list()[1]->as_string());
    EXPECT_EQ(1, node->get("modules")->as_map().size());
    EXPECT_EQ(2, node->get("modules")->as_map()["enable"]->as_list().size());
    EXPECT_EQ("module1", node->get("modules")->as_map()["enable"]->as_list()[0]->as_string());
    EXPECT_EQ("module2", node->get("modules")->as_map()["enable"]->as_list()[1]->as_string());
    EXPECT_EQ("arch1", node->get("archs")->as_list()[0]->as_string());
    EXPECT_EQ("arch2", node->get("archs")->as_list()[1]->as_string());
    EXPECT_EQ(1, node->get("options")->as_map().size());
    EXPECT_EQ(true, node->get("options")->as_map()["allow_erasing"]->as_bool());
}

}