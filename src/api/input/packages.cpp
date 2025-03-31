#include "packages_impl.hpp"

#include "libpkgmanifest/input/packages.hpp"

namespace libpkgmanifest::input {

Packages::Packages() : p_impl(std::make_unique<Impl>()) {}

Packages::~Packages() = default;

Packages::Packages(const Packages & other) : p_impl(new Impl(*other.p_impl)) {}

Packages & Packages::operator=(const Packages & other) {
    if (this != &other) {
        *p_impl = *other.p_impl;
    }
    return *this;
}

Packages::Packages(Packages && other) noexcept = default;
Packages & Packages::operator=(Packages && other) noexcept = default;

std::vector<std::string> & Packages::get_installs() {
    return p_impl->get()->get_installs();
}

std::vector<std::string> & Packages::get_reinstalls() {
    return p_impl->get()->get_reinstalls();
}

}