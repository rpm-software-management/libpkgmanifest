#include "validatorfactory.hpp"
#include "validator.hpp"

namespace libpkgmanifest::internal {

std::unique_ptr<IValidator> ValidatorFactory::create() const {
    throw; // TODO
}

}