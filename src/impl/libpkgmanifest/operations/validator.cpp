#include "validator.hpp"

#include "libpkgmanifest/config.h"

namespace libpkgmanifest::internal {

Validator::Validator(std::unique_ptr<IYamlValidator> yaml_validator)
    : yaml_validator(std::move(yaml_validator)) {}

void Validator::validate(const std::string & path) const {
    auto schema_path = std::string(LIBPKGMANIFEST_LIB_DIR) + SCHEMA_FILENAME;
    yaml_validator->validate(path, schema_path);
}

}