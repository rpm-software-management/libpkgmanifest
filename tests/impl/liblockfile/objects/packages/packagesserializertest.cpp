#include "liblockfile/mocks/objects/package/packagemock.hpp"
#include "liblockfile/mocks/objects/package/packageserializermock.hpp"
#include "liblockfile/mocks/objects/packages/packagesmock.hpp"
#include "liblockfile/mocks/yaml/yamlnodefactorymock.hpp"
#include "liblockfile/mocks/yaml/yamlnodeinternalmock.hpp"
#include "liblockfile/mocks/yaml/yamlnodeinternalstub.hpp"

#include "liblockfile/objects/packages/packagesserializer.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace liblockfile::internal;

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Ref;
using ::testing::Return;
using ::testing::ReturnPointee;
using ::testing::Test;

class PackagesSerializerTest : public Test {
protected:
    virtual void SetUp() {
        auto package_serializer = std::make_unique<NiceMock<PackageSerializerMock>>();
        package_serializer_ptr = package_serializer.get();

        auto node = std::make_unique<NiceMock<YamlNodeInternalMock>>();
        node_ptr = node.get();

        auto node_factory = std::make_shared<NiceMock<YamlNodeFactoryMock>>();
        EXPECT_CALL(*node_factory, create())
            .WillOnce(Return(std::move(node)))
            .WillRepeatedly([]() { 
                return std::make_unique<YamlNodeInternalStub>(); 
            });

        serializer = std::make_unique<PackagesSerializer>(node_factory, std::move(package_serializer));
    }

    NiceMock<PackagesMock> packages;
    NiceMock<YamlNodeInternalMock> * node_ptr;
    NiceMock<PackageSerializerMock> * package_serializer_ptr;
    std::unique_ptr<PackagesSerializer> serializer;
};

TEST_F(PackagesSerializerTest, SerializerCreatesListNodeOfPackagesFromSerializerForEachArch) {
    auto arch1_pkg1 = std::make_unique<NiceMock<PackageMock>>();
    auto arch1_pkg1_ptr = arch1_pkg1.get();
    auto arch1_pkg1_node = std::make_unique<YamlNodeInternalStub>();
    auto arch1_pkg1_node_ptr = arch1_pkg1_node.get();
    arch1_pkg1_node_ptr->set("arch1_pkg1");
    auto arch1_pkg2 = std::make_unique<NiceMock<PackageMock>>();
    auto arch1_pkg2_ptr = arch1_pkg2.get();
    auto arch1_pkg2_node = std::make_unique<YamlNodeInternalStub>();
    auto arch1_pkg2_node_ptr = arch1_pkg2_node.get();
    arch1_pkg2_node_ptr->set("arch1_pkg2");
    std::vector<std::unique_ptr<IPackage>> arch1_pkgs;
    arch1_pkgs.push_back(std::move(arch1_pkg1));
    arch1_pkgs.push_back(std::move(arch1_pkg2));

    auto arch2_pkg1 = std::make_unique<NiceMock<PackageMock>>();
    auto arch2_pkg1_ptr = arch2_pkg1.get();
    auto arch2_pkg1_node = std::make_unique<YamlNodeInternalStub>();
    auto arch2_pkg1_node_ptr = arch2_pkg1_node.get();
    arch2_pkg1_node_ptr->set("arch2_pkg1");
    std::vector<std::unique_ptr<IPackage>> arch2_pkgs;
    arch2_pkgs.push_back(std::move(arch2_pkg1));

    EXPECT_CALL(*package_serializer_ptr, serialize(Ref(*arch1_pkg1_ptr)))
        .WillOnce(Return(std::move(arch1_pkg1_node)));
    EXPECT_CALL(*package_serializer_ptr, serialize(Ref(*arch1_pkg2_ptr)))
        .WillOnce(Return(std::move(arch1_pkg2_node)));
    EXPECT_CALL(*package_serializer_ptr, serialize(Ref(*arch2_pkg1_ptr)))
        .WillOnce(Return(std::move(arch2_pkg1_node)));

    std::map<std::string, std::vector<std::unique_ptr<IPackage>>> map;
    map["arch1"] = std::move(arch1_pkgs);
    map["arch2"] = std::move(arch2_pkgs);

    EXPECT_CALL(packages, get()).WillOnce(ReturnPointee(&map));
    EXPECT_CALL(*node_ptr, insert("arch1", _)).WillOnce(
    [&](const std::string &, std::unique_ptr<IYamlNode> node) {
        auto const & node_list = node->as_list();
        EXPECT_EQ(2, node_list.size());
        EXPECT_EQ("arch1_pkg1", node_list[0].get()->as_string());
        EXPECT_EQ("arch1_pkg2", node_list[1].get()->as_string());
    });

    EXPECT_CALL(*node_ptr, insert("arch2", _)).WillOnce(
    [&](const std::string &, std::unique_ptr<IYamlNode> node) {
        auto const & node_list = node->as_list();
        EXPECT_EQ(1, node_list.size());
        EXPECT_EQ("arch2_pkg1", node_list[0].get()->as_string());
    });

    serializer->serialize(packages);
}

TEST_F(PackagesSerializerTest, SerializerReturnsTheObjectCreatedByFactory) {
    std::map<std::string, std::vector<std::unique_ptr<IPackage>>> map;
    EXPECT_CALL(packages, get()).WillOnce(ReturnPointee(&map));

    auto serialized_node = serializer->serialize(packages);
    EXPECT_EQ(serialized_node.get(), node_ptr);
}

}