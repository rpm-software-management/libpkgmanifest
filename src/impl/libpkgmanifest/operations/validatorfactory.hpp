#pragma once

#include "ivalidatorfactory.hpp"

namespace libpkgmanifest::internal {

class ValidatorFactory : public IValidatorFactory {
public:
    virtual std::unique_ptr<IValidator> create() const override;
};

}