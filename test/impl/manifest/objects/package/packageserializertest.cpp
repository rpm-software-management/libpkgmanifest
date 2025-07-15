// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/manifest/mocks/objects/checksum/checksummock.hpp"
#include "impl/manifest/mocks/objects/checksum/checksumserializermock.hpp"
#include "impl/manifest/mocks/objects/module/modulemock.hpp"
#include "impl/manifest/mocks/objects/module/moduleserializermock.hpp"
#include "impl/manifest/mocks/objects/nevra/nevramock.hpp"
#include "impl/manifest/mocks/objects/package/packagemock.hpp"
#include "impl/common/mocks/yaml/yamlnodefactorymock.hpp"
#include "impl/common/mocks/yaml/yamlnodemock.hpp"
#include "impl/common/mocks/yaml/yamlnodeinternalmock.hpp"
#include "impl/common/mocks/yaml/yamlnodeinternalstub.hpp"

#include "impl/manifest/objects/package/packageserializer.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal::manifest;

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::NiceMock;
using ::testing::Pointer;
using ::testing::Ref;
using ::testing::Return;
using ::testing::ReturnPointee;
using ::testing::Test;

class PackageSerializerTest : public Test {
protected:
    virtual void SetUp() {
        auto checksum_serializer = std::make_unique<NiceMock<ChecksumSerializerMock>>();
        checksum_serializer_ptr = checksum_serializer.get();

        auto module_serializer = std::make_unique<NiceMock<ModuleSerializerMock>>();
        module_serializer_ptr = module_serializer.get();

        auto node = std::make_unique<NiceMock<YamlNodeInternalMock>>();
        node_ptr = node.get();
        EXPECT_CALL(*node_ptr, insert(_, _)).Times(AnyNumber());

        auto node_factory = std::make_shared<NiceMock<YamlNodeFactoryMock>>();
        EXPECT_CALL(*node_factory, create())
            .WillOnce(Return(std::move(node)))
            .WillRepeatedly([]() { 
                return std::make_unique<YamlNodeInternalStub>(); 
            });
        
        EXPECT_CALL(Const(package), get_checksum()).WillOnce(ReturnPointee(&checksum));
        EXPECT_CALL(Const(package), get_module()).WillOnce(ReturnPointee(&module));
        EXPECT_CALL(Const(package), get_nevra()).WillRepeatedly(ReturnPointee(&nevra));
        EXPECT_CALL(Const(package), get_srpm()).WillOnce(ReturnPointee(&srpm));
        EXPECT_CALL(Const(package), get_parent_archs()).WillRepeatedly(ReturnPointee(&parent_archs));

        serializer = std::make_unique<PackageSerializer>(
            node_factory, 
            std::move(checksum_serializer),
            std::move(module_serializer));
    }

    NiceMock<PackageMock> package;
    NiceMock<ChecksumMock> checksum;
    NiceMock<ModuleMock> module;
    NiceMock<NevraMock> nevra;
    NiceMock<NevraMock> srpm;
    NiceMock<YamlNodeInternalMock> * node_ptr;
    NiceMock<ChecksumSerializerMock> * checksum_serializer_ptr;
    NiceMock<ModuleSerializerMock> * module_serializer_ptr;
    std::vector<std::string> parent_archs;
    std::unique_ptr<PackageSerializer> serializer;
};

TEST_F(PackageSerializerTest, SerializerSetsRepoIdAsStringToYamlNode) {
    EXPECT_CALL(package, get_repo_id()).WillOnce(Return("repo1"));

    EXPECT_CALL(*node_ptr, insert("repo_id", _)).WillOnce(
        [](const std::string &, std::unique_ptr<IYamlNode> node) {
            EXPECT_EQ("repo1", node->as_string());
        });

    serializer->serialize(package);
}

TEST_F(PackageSerializerTest, SerializerSetsLocationAsStringToYamlNode) {
    EXPECT_CALL(package, get_location()).WillOnce(Return("address"));

    EXPECT_CALL(*node_ptr, insert("location", _)).WillOnce(
    [](const std::string &, std::unique_ptr<IYamlNode> node) {
        EXPECT_EQ("address", node->as_string());
    });

    serializer->serialize(package);
}

TEST_F(PackageSerializerTest, SerializerDoesNotSetLocationIfEmpty) {
    EXPECT_CALL(package, get_location()).WillOnce(Return(""));
    EXPECT_CALL(*node_ptr, insert("location", _)).Times(0);

    serializer->serialize(package);
}

TEST_F(PackageSerializerTest, SerializerSetsChecksumFromChecksumSerializer) {
    auto checksum_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto checksum_node_ptr = checksum_node.get();
    EXPECT_CALL(*checksum_serializer_ptr, serialize(Ref(checksum))).WillOnce(Return(std::move(checksum_node)));

    EXPECT_CALL(*node_ptr, insert("checksum", Pointer(checksum_node_ptr)));

    serializer->serialize(package);
}

TEST_F(PackageSerializerTest, SerializerSetsSizeAsUInt64ToYamlNode) {
    EXPECT_CALL(package, get_size()).WillOnce(Return(123456789123456789U));

    EXPECT_CALL(*node_ptr, insert("size", _)).WillOnce(
    [](const std::string &, std::unique_ptr<IYamlNode> node) {
        EXPECT_EQ(123456789123456789U, node->as_uint64());
    });

    serializer->serialize(package);
}

TEST_F(PackageSerializerTest, SerializerSetsNameFromNevraObjectAsStringToYamlNode) {
    EXPECT_CALL(nevra, get_name()).WillOnce(Return("package"));

    EXPECT_CALL(*node_ptr, insert("name", _)).WillOnce(
    [](const std::string &, std::unique_ptr<IYamlNode> node) {
        EXPECT_EQ("package", node->as_string());
    });

    serializer->serialize(package);
}

TEST_F(PackageSerializerTest, SerializerSetsEpochVersionReleaseFromNevraToEvrString) {
    EXPECT_CALL(nevra, to_evr_string()).WillOnce(Return("evr-string"));

    EXPECT_CALL(*node_ptr, insert("evr", _)).WillOnce(
    [](const std::string &, std::unique_ptr<IYamlNode> node) {
        EXPECT_EQ("evr-string", node->as_string());
    });

    serializer->serialize(package);
}

TEST_F(PackageSerializerTest, SerializerSetsSrpmNEVRAFromToString) {
    EXPECT_CALL(srpm, get_name()).WillOnce(Return("package"));
    EXPECT_CALL(srpm, to_string()).WillOnce(Return("src-nevra"));

    EXPECT_CALL(*node_ptr, insert("srpm", _)).WillOnce(
    [](const std::string &, std::unique_ptr<IYamlNode> node) {
        EXPECT_EQ("src-nevra", node->as_string());
    });

    serializer->serialize(package);
}

TEST_F(PackageSerializerTest, SerializerDoesNotSetSrpmIfEmpty) {
    EXPECT_CALL(srpm, get_name()).WillOnce(Return(""));
    EXPECT_CALL(*node_ptr, insert("srpm", _)).Times(0);

    serializer->serialize(package);
}

TEST_F(PackageSerializerTest, SerializerSetsModuleFromModuleSerializer) {
    EXPECT_CALL(module, get_name()).WillOnce(Return("name"));

    auto module_node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto module_node_ptr = module_node.get();
    EXPECT_CALL(*module_serializer_ptr, serialize(Ref(module))).WillOnce(Return(std::move(module_node)));

    EXPECT_CALL(*node_ptr, insert("module", Pointer(module_node_ptr)));

    serializer->serialize(package);
}

TEST_F(PackageSerializerTest, SerializerDoesNotSetModuleIfEmpty) {
    EXPECT_CALL(module, get_name()).WillOnce(Return(""));
    EXPECT_CALL(*node_ptr, insert("module", _)).Times(0);

    serializer->serialize(package);
}

TEST_F(PackageSerializerTest, SerializerSetsParentArchsToNodeAsList) {
    parent_archs = {"arch1", "arch2"};

    EXPECT_CALL(*node_ptr, insert("parent_archs", _)).WillOnce(
    [](const std::string &, std::unique_ptr<IYamlNode> node) {
        auto list = node->as_list();
        ASSERT_EQ(2, list.size());
        EXPECT_EQ("arch1", list[0]->as_string());
        EXPECT_EQ("arch2", list[1]->as_string());
    });

    serializer->serialize(package);
}

TEST_F(PackageSerializerTest, SerializerDoesNotSetParentArchsIfEmpty) {
    parent_archs = {};
    EXPECT_CALL(*node_ptr, insert("parent_archs", _)).Times(0);
    serializer->serialize(package);
}

TEST_F(PackageSerializerTest, SerializerReturnsTheObjectCreatedByFactory) {
    auto serialized_node = serializer->serialize(package);
    EXPECT_EQ(serialized_node.get(), node_ptr);
}

}