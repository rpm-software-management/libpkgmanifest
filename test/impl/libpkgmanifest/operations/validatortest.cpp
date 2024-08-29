#include "libpkgmanifest/mocks/yaml/yamlvalidatormock.hpp"

#include "libpkgmanifest/operations/validator.hpp"

#include "libpkgmanifest/config.h"

#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal;

using ::testing::NiceMock;

TEST(ValidatorTest, FilePathAndSchemaPathArePassedToYamlValidator) {
    auto yaml_validator = std::make_unique<NiceMock<YamlValidatorMock>>();
    auto yaml_validator_ptr = yaml_validator.get();

    Validator validator(std::move(yaml_validator));

    auto file_path = "testing-file-path";
    auto schema_path = std::string(LIBPKGMANIFEST_LIB_DIR) + SCHEMA_FILENAME;

    EXPECT_CALL(*yaml_validator_ptr, validate(file_path, schema_path));

    validator.validate(file_path);
}

}