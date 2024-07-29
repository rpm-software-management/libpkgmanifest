#include "liblockfile/packages.hpp"

#include "packages_impl.hpp"

namespace liblockfile {

Packages::Packages() : p_impl(std::make_unique<Impl>()) {}

Packages::~Packages() = default;

const std::map<std::string, std::vector<Package>> & Packages::get() const {
    return p_impl->packages_map;
}

const std::vector<Package> & Packages::get(const std::string & arch) const {
    return p_impl->packages_map[arch];
}

}