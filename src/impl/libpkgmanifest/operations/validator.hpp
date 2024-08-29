#pragma once

#include "ivalidator.hpp"

#include "libpkgmanifest/yaml/iyamlvalidator.hpp"

#include <memory>

namespace libpkgmanifest::internal {

constexpr const char SCHEMA_FILENAME[] = "manifest.json";

class Validator : public IValidator {
public:
    Validator(std::unique_ptr<IYamlValidator> yaml_validator);

    virtual void validate(const std::string & path) const override;

private:
    std::unique_ptr<IYamlValidator> yaml_validator;
};

}