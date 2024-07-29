#include "liblockfile/mocks/objects/lockfile/lockfilemock.hpp"
#include "liblockfile/mocks/objects/lockfile/lockfileserializermock.hpp"
#include "liblockfile/mocks/yaml/yamlnodemock.hpp"
#include "liblockfile/mocks/yaml/yamlserializermock.hpp"

#include "liblockfile/wrappers/serializer.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace liblockfile::internal;

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Return;

TEST(SerializerTest, LockFileIsPassedOverToYamlSerializer) {
    NiceMock<LockFileMock> file;

    auto node = std::make_unique<NiceMock<YamlNodeMock>>();
    auto node_ptr = node.get();

    auto yaml_serializer = std::make_unique<NiceMock<YamlSerializerMock>>();
    auto yaml_serializer_ptr = yaml_serializer.get();
    auto file_serializer = std::make_unique<NiceMock<LockFileSerializerMock>>();
    auto file_serializer_ptr = file_serializer.get();

    Serializer serializer(std::move(yaml_serializer), std::move(file_serializer));

    EXPECT_CALL(*file_serializer_ptr, serialize(Ref(file))).WillOnce(Return(std::move(node)));
    EXPECT_CALL(*yaml_serializer_ptr, to_file(Ref(*node_ptr), "path"));

    serializer.serialize(file, "path");
}

}