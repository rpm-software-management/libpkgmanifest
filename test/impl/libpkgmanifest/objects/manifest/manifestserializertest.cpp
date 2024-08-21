#include "libpkgmanifest/mocks/objects/manifest/manifestmock.hpp"
#include "libpkgmanifest/mocks/objects/packages/packagesmock.hpp"
#include "libpkgmanifest/mocks/objects/packages/packagesserializermock.hpp"
#include "libpkgmanifest/mocks/objects/version/versionmock.hpp"
#include "libpkgmanifest/mocks/objects/version/versionserializermock.hpp"
#include "libpkgmanifest/mocks/yaml/yamlnodefactorymock.hpp"
#include "libpkgmanifest/mocks/yaml/yamlnodeinternalmock.hpp"
#include "libpkgmanifest/mocks/yaml/yamlnodeinternalstub.hpp"

#include "libpkgmanifest/objects/manifest/manifestserializer.hpp"

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
using ::testing::Test;

class ManifestSerializerTest : public Test {
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
        
        EXPECT_CALL(Const(manifest), get_packages()).WillOnce(ReturnPointee(&packages));
        EXPECT_CALL(Const(manifest), get_version()).WillOnce(ReturnPointee(&version));

        serializer = std::make_unique<ManifestSerializer>(node_factory, std::move(packages_serializer), std::move(version_serializer));
    }

    NiceMock<ManifestMock> manifest;
    NiceMock<PackagesMock> packages;
    NiceMock<VersionMock> version;
    NiceMock<YamlNodeInternalMock> * node_ptr;
    NiceMock<PackagesSerializerMock> * packages_serializer_ptr;
    NiceMock<VersionSerializerMock> * version_serializer_ptr;
    std::unique_ptr<ManifestSerializer> serializer;
};

TEST_F(ManifestSerializerTest, SerializerSetsDocumentAsStringToYamlNode) {
    EXPECT_CALL(manifest, get_document()).WillOnce(Return("rpm-manifest"));

    EXPECT_CALL(*node_ptr, insert("document", _)).WillOnce(
        [](const std::string &, std::unique_ptr<IYamlNode> node) {
            EXPECT_EQ("rpm-manifest", node->as_string());
        });

    serializer->serialize(manifest);
}

TEST_F(ManifestSerializerTest, SerializerSetsVersionFromPackagesSerializer) {
    auto version_node = std::make_unique<NiceMock<YamlNodeInternalStub>>();
    auto version_node_ptr = version_node.get();
    EXPECT_CALL(*version_serializer_ptr, serialize(Ref(version))).WillOnce(Return(std::move(version_node)));

    EXPECT_CALL(*node_ptr, insert("version", Pointer(version_node_ptr)));

    serializer->serialize(manifest);
}

TEST_F(ManifestSerializerTest, SerializerSetsPackagesFromPackagesSerializer) {
    auto packages_node = std::make_unique<NiceMock<YamlNodeInternalStub>>();
    auto packages_node_ptr = packages_node.get();
    packages_node_ptr->set("packages_node");

    EXPECT_CALL(*packages_serializer_ptr, serialize(Ref(packages))).WillOnce(Return(std::move(packages_node)));

    EXPECT_CALL(*node_ptr, insert("data", _)).WillOnce(
        [](const std::string &, std::unique_ptr<IYamlNode> node) {
            EXPECT_EQ("packages_node", node->get("packages")->as_string());
        });

    serializer->serialize(manifest);
}

TEST_F(ManifestSerializerTest, SerializerReturnsTheObjectCreatedByFactory) {
    auto serialized_node = serializer->serialize(manifest);
    EXPECT_EQ(serialized_node.get(), node_ptr);
}

}