#include "liblockfile/mocks/objects/lockfile/lockfilemock.hpp"
#include "liblockfile/mocks/objects/packages/packagesmock.hpp"
#include "liblockfile/mocks/objects/packages/packagesserializermock.hpp"
#include "liblockfile/mocks/objects/version/versionmock.hpp"
#include "liblockfile/mocks/objects/version/versionserializermock.hpp"
#include "liblockfile/mocks/yaml/yamlnodefactorymock.hpp"
#include "liblockfile/mocks/yaml/yamlnodeinternalmock.hpp"
#include "liblockfile/mocks/yaml/yamlnodeinternalstub.hpp"

#include "liblockfile/objects/lockfile/lockfileserializer.hpp"

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

class LockFileSerializerTest : public Test {
protected:
    virtual void SetUp() {
        auto packages_serializer = std::make_unique<NiceMock<PackagesSerializerMock>>();
        packages_serializer_ptr = packages_serializer.get();

        auto version_serializer = std::make_unique<NiceMock<VersionSerializerMock>>();
        version_serializer_ptr = version_serializer.get();

        auto node = std::make_unique<NiceMock<YamlNodeInternalMock>>();
        node_ptr = node.get();
        EXPECT_CALL(*node_ptr, insert(_, _)).Times(AnyNumber());

        auto node_factory = std::make_shared<NiceMock<YamlNodeFactoryMock>>();
        EXPECT_CALL(*node_factory, create())
            .WillOnce(Return(std::move(node)))
            .WillRepeatedly([]() { 
                return std::make_unique<YamlNodeInternalStub>(); 
            });
        
        EXPECT_CALL(file, get_packages()).WillOnce(ReturnPointee(&packages));
        EXPECT_CALL(file, get_version()).WillOnce(ReturnPointee(&version));

        serializer = std::make_unique<LockFileSerializer>(node_factory, std::move(packages_serializer), std::move(version_serializer));
    }

    NiceMock<LockFileMock> file;
    NiceMock<PackagesMock> packages;
    NiceMock<VersionMock> version;
    NiceMock<YamlNodeInternalMock> * node_ptr;
    NiceMock<PackagesSerializerMock> * packages_serializer_ptr;
    NiceMock<VersionSerializerMock> * version_serializer_ptr;
    std::unique_ptr<LockFileSerializer> serializer;
};

TEST_F(LockFileSerializerTest, SerializerSetsDocumentAsStringToYamlNode) {
    EXPECT_CALL(file, get_document()).WillOnce(Return("rpm-lockfile"));

    EXPECT_CALL(*node_ptr, insert("document", _)).WillOnce(
        [](const std::string &, std::unique_ptr<IYamlNode> node) {
            EXPECT_EQ("rpm-lockfile", node->as_string());
        });

    serializer->serialize(file);
}

TEST_F(LockFileSerializerTest, SerializerSetsVersionFromPackagesSerializer) {
    auto version_node = std::make_unique<NiceMock<YamlNodeInternalStub>>();
    auto version_node_ptr = version_node.get();
    EXPECT_CALL(*version_serializer_ptr, serialize(Ref(version))).WillOnce(Return(std::move(version_node)));

    EXPECT_CALL(*node_ptr, insert("version", Pointer(version_node_ptr)));

    serializer->serialize(file);
}

TEST_F(LockFileSerializerTest, SerializerSetsPackagesFromPackagesSerializer) {
    auto packages_node = std::make_unique<NiceMock<YamlNodeInternalStub>>();
    auto packages_node_ptr = packages_node.get();
    packages_node_ptr->set("packages_node");

    EXPECT_CALL(*packages_serializer_ptr, serialize(Ref(packages))).WillOnce(Return(std::move(packages_node)));

    EXPECT_CALL(*node_ptr, insert("data", _)).WillOnce(
        [](const std::string &, std::unique_ptr<IYamlNode> node) {
            EXPECT_EQ("packages_node", node->get("packages")->as_string());
        });

    serializer->serialize(file);
}

TEST_F(LockFileSerializerTest, SerializerReturnsTheObjectCreatedByFactory) {
    auto serialized_node = serializer->serialize(file);
    EXPECT_EQ(serialized_node.get(), node_ptr);
}

}