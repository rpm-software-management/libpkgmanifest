#include "packages_impl.hpp"

#include "liblockfile/packages.hpp"

namespace liblockfile {

Packages::Packages() : p_impl(std::make_unique<Impl>()) {}

Packages::~Packages() = default;

Packages::Packages(const Packages & other) : p_impl(new Impl(*other.p_impl)) {}

Packages & Packages::operator=(const Packages & other) {
    if (this != &other) {
        if (p_impl) {
            *p_impl = *other.p_impl;
        } else {
            p_impl = std::make_unique<Impl>(*other.p_impl);
        }
    }

    return *this;
}

Packages::Packages(Packages && other) noexcept = default;
Packages & Packages::operator=(Packages && other) noexcept = default;

const std::map<std::string, std::vector<Package>> & Packages::get() const {
    return p_impl->packages_map;
}

const std::vector<Package> & Packages::get(const std::string & arch) const {
    return p_impl->packages_map.at(arch);
}

}