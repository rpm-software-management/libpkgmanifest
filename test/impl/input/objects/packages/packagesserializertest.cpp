// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/common/mocks/yaml/yamlnodefactorymock.hpp"
#include "impl/common/mocks/yaml/yamlnodeinternalmock.hpp"
#include "impl/common/mocks/yaml/yamlnodeinternalstub.hpp"
#include "impl/input/mocks/objects/packages/packagesmock.hpp"
#include "impl/input/objects/packages/packagesserializer.hpp"

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

class InputPackagesSerializerTest : public Test {
protected:
    virtual void SetUp() {
        auto node = std::make_unique<NiceMock<YamlNodeInternalMock>>();
        node_ptr = node.get();
        EXPECT_CALL(*node_ptr, insert(_, _)).Times(AnyNumber());

        auto node_factory = std::make_shared<NiceMock<YamlNodeFactoryMock>>();
        EXPECT_CALL(*node_factory, create()).WillOnce(Return(std::move(node))).WillRepeatedly([]() {
            return std::make_unique<YamlNodeInternalStub>();
        });

        serializer = std::make_unique<PackagesSerializer>(node_factory);
    }

    NiceMock<PackagesMock> packages;
    NiceMock<YamlNodeInternalMock> * node_ptr;
    std::unique_ptr<PackagesSerializer> serializer;
};

TEST_F(InputPackagesSerializerTest, SerializerSetsInstallListToYamlNode) {
    std::vector<std::string> installs = {"pkg1", "pkg2", "pkg3"};
    std::vector<std::string> reinstalls;
    EXPECT_CALL(Const(packages), get_installs()).WillOnce(ReturnPointee(&installs));
    EXPECT_CALL(Const(packages), get_reinstalls()).WillOnce(ReturnPointee(&reinstalls));

    EXPECT_CALL(*node_ptr, insert("install", _)).WillOnce([](const std::string &, std::unique_ptr<IYamlNode> node) {
        auto const & node_list = node->as_list();
        EXPECT_EQ(3, node_list.size());
        EXPECT_EQ("pkg1", node_list[0]->as_string());
        EXPECT_EQ("pkg2", node_list[1]->as_string());
        EXPECT_EQ("pkg3", node_list[2]->as_string());
    });

    serializer->serialize(packages);
}

TEST_F(InputPackagesSerializerTest, SerializerSetsReinstallListToYamlNodeWhenNotEmpty) {
    std::vector<std::string> installs = {"pkg1"};
    std::vector<std::string> reinstalls = {"rpkg1", "rpkg2"};
    EXPECT_CALL(Const(packages), get_installs()).WillOnce(ReturnPointee(&installs));
    EXPECT_CALL(Const(packages), get_reinstalls()).WillRepeatedly(ReturnPointee(&reinstalls));

    EXPECT_CALL(*node_ptr, insert("reinstall", _)).WillOnce([](const std::string &, std::unique_ptr<IYamlNode> node) {
        auto const & node_list = node->as_list();
        EXPECT_EQ(2, node_list.size());
        EXPECT_EQ("rpkg1", node_list[0]->as_string());
        EXPECT_EQ("rpkg2", node_list[1]->as_string());
    });

    serializer->serialize(packages);
}

TEST_F(InputPackagesSerializerTest, SerializerDoesNotSetReinstallWhenEmpty) {
    std::vector<std::string> installs = {"pkg1"};
    std::vector<std::string> reinstalls;
    EXPECT_CALL(Const(packages), get_installs()).WillOnce(ReturnPointee(&installs));
    EXPECT_CALL(Const(packages), get_reinstalls()).WillOnce(ReturnPointee(&reinstalls));

    EXPECT_CALL(*node_ptr, insert("reinstall", _)).Times(0);

    serializer->serialize(packages);
}

TEST_F(InputPackagesSerializerTest, SerializerReturnsTheObjectCreatedByFactory) {
    std::vector<std::string> installs;
    std::vector<std::string> reinstalls;
    EXPECT_CALL(Const(packages), get_installs()).WillOnce(ReturnPointee(&installs));
    EXPECT_CALL(Const(packages), get_reinstalls()).WillOnce(ReturnPointee(&reinstalls));

    auto serialized_node = serializer->serialize(packages);
    EXPECT_EQ(serialized_node.get(), node_ptr);
}

}  // namespace
