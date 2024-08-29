#pragma once

#include "iyamlvalidator.hpp"

namespace libpkgmanifest::internal {

class YamlValidator : public IYamlValidator {
public:
    virtual void validate(const std::string & file_path, const std::string & schema_path) const override;
};

}