#pragma once

#include <string>

namespace libpkgmanifest::internal {

class IValidator {
public:
    virtual ~IValidator() = default;

    virtual void validate(const std::string & path) const = 0;
};

}