#include "options.hpp"

namespace libpkgmanifest::internal::input {

Options::Options()
    : allow_erasing(false) {}

std::unique_ptr<IOptions> Options::clone() const {
    return std::unique_ptr<IOptions>(new Options(*this));
}

bool Options::get_allow_erasing() const {
    return allow_erasing;
}

void Options::set_allow_erasing(bool allow_erasing) {
    this->allow_erasing = allow_erasing;
}

}
