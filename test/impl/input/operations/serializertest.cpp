// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/common/mocks/yaml/yamlnodemock.hpp"
#include "impl/common/mocks/yaml/yamlserializermock.hpp"
#include "impl/input/mocks/objects/input/inputmock.hpp"
#include "impl/input/mocks/objects/input/inputserializermock.hpp"
#include "impl/input/operations/serializer/serializer.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal::input;

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Return;

TEST(InputSerializerOperationsTest, InputIsPassedOverToYamlSerializer) {
    NiceMock<InputMock> input;

    auto node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto node_ptr = node.get();

    auto yaml_serializer = std::make_unique<NiceMock<YamlSerializerMock>>();
    auto yaml_serializer_ptr = yaml_serializer.get();
    auto input_serializer = std::make_unique<NiceMock<InputSerializerMock>>();
    auto input_serializer_ptr = input_serializer.get();

    Serializer serializer(std::move(yaml_serializer), std::move(input_serializer));

    EXPECT_CALL(*input_serializer_ptr, serialize(Ref(input))).WillOnce(Return(std::move(node)));
    EXPECT_CALL(*yaml_serializer_ptr, to_file(Ref(*node_ptr), "path"));

    serializer.serialize_input(input, "path");
}

}  // namespace
