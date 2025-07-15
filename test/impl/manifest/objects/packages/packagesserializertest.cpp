// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/manifest/mocks/objects/package/packagemock.hpp"
#include "impl/manifest/mocks/objects/package/packageserializermock.hpp"
#include "impl/manifest/mocks/objects/packages/packagesmock.hpp"
#include "impl/common/mocks/yaml/yamlnodefactorymock.hpp"
#include "impl/common/mocks/yaml/yamlnodeinternalmock.hpp"
#include "impl/common/mocks/yaml/yamlnodeinternalstub.hpp"

#include "impl/manifest/objects/packages/packagesserializer.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal::manifest;

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

    EXPECT_CALL(packages, get_archs()).WillOnce(Return(std::vector<std::string>{"arch1", "arch2"}));

    EXPECT_CALL(packages, get("arch1")).WillOnce(ReturnPointee(&arch1_pkgs));
    EXPECT_CALL(*node_ptr, insert("arch1", _)).WillOnce(
    [&](const std::string &, std::unique_ptr<IYamlNode> node) {
        auto const & node_list = node->as_list();
        EXPECT_EQ(2, node_list.size());
        EXPECT_EQ("arch1_pkg1", node_list[0].get()->as_string());
        EXPECT_EQ("arch1_pkg2", node_list[1].get()->as_string());
    });

    EXPECT_CALL(packages, get("arch2")).WillOnce(ReturnPointee(&arch2_pkgs));
    EXPECT_CALL(*node_ptr, insert("arch2", _)).WillOnce(
    [&](const std::string &, std::unique_ptr<IYamlNode> node) {
        auto const & node_list = node->as_list();
        EXPECT_EQ(1, node_list.size());
        EXPECT_EQ("arch2_pkg1", node_list[0].get()->as_string());
    });

    serializer->serialize(packages);
}

TEST_F(PackagesSerializerTest, SerializerReturnsTheObjectCreatedByFactory) {
    std::vector<std::string> archs;
    EXPECT_CALL(Const(packages), get_archs()).WillOnce(ReturnPointee(&archs));

    auto serialized_node = serializer->serialize(packages);
    EXPECT_EQ(serialized_node.get(), node_ptr);
}

}