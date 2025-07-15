// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/manifest/mocks/objects/manifest/manifestmock.hpp"
#include "impl/manifest/mocks/objects/manifest/manifestserializermock.hpp"
#include "impl/common/mocks/yaml/yamlnodemock.hpp"
#include "impl/common/mocks/yaml/yamlserializermock.hpp"

#include "impl/manifest/operations/serializer/serializer.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal::manifest;

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Return;

TEST(SerializerTest, ManifestIsPassedOverToYamlSerializer) {
    NiceMock<ManifestMock> manifest;

    auto node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto node_ptr = node.get();

    auto yaml_serializer = std::make_unique<NiceMock<YamlSerializerMock>>();
    auto yaml_serializer_ptr = yaml_serializer.get();
    auto manifest_serializer = std::make_unique<NiceMock<ManifestSerializerMock>>();
    auto manifest_serializer_ptr = manifest_serializer.get();

    Serializer serializer(std::move(yaml_serializer), std::move(manifest_serializer));

    EXPECT_CALL(*manifest_serializer_ptr, serialize(Ref(manifest))).WillOnce(Return(std::move(node)));
    EXPECT_CALL(*yaml_serializer_ptr, to_file(Ref(*node_ptr), "path"));

    serializer.serialize_manifest(manifest, "path");
}

}