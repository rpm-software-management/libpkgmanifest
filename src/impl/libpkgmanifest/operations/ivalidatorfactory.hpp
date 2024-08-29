#pragma once

#include "ivalidator.hpp"

#include <memory>

namespace libpkgmanifest::internal {

class IValidatorFactory {
public:
    virtual ~IValidatorFactory() = default;

    virtual std::unique_ptr<IValidator> create() const = 0;
};

}