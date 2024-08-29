#include "libpkgmanifest/validator.hpp"

#include "libpkgmanifest/operations/validatorfactory.hpp"

namespace libpkgmanifest {

class Validator::Impl {
public:
    Impl() {
        validator = internal::ValidatorFactory().create();
    }
private:
    friend Validator;
    std::unique_ptr<internal::IValidator> validator;
};

Validator::Validator() : p_impl(std::make_unique<Impl>()) {}

Validator::~Validator() = default;

void Validator::validate(const std::string & path) const {
    p_impl->validator->validate(path);
}

}