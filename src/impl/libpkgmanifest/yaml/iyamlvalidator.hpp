#pragma once

#include <string>

namespace libpkgmanifest::internal {

class IYamlValidator {
public:
    virtual ~IYamlValidator() = default;

    virtual void validate(const std::string & file_path, const std::string & schema_path) const = 0;
};

}