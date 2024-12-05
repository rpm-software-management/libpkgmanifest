#include "packages_impl.hpp"

#include "api/common/repositories_impl.hpp"

#include "libpkgmanifest/manifest/packages.hpp"

namespace libpkgmanifest::manifest {

using namespace libpkgmanifest::common;

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

std::vector<Package> Packages::get() const {
    std::vector<Package> all_packages;
    for (const auto & [_, packages] : p_impl->get()->get()) {
        auto wrapped_packages = p_impl->wrap_internal_items(packages);
        all_packages.insert(all_packages.end(), wrapped_packages.begin(), wrapped_packages.end());
    }
    return all_packages;
}

std::vector<Package> Packages::get(const std::string & arch) const {
    // TODO: Exception when no such arch
    return p_impl->wrap_internal_items(p_impl->get()->get()[arch]);
}

void Packages::add(Package & package) {
    p_impl->get()->add(package.p_impl->get_factory_object());
}

bool Packages::contains(const Package & package) {
    return p_impl->get()->contains(*package.p_impl->get());
}

void Packages::attach(Repositories & repositories) {
    p_impl->get_binder().bind(*repositories.p_impl->get(), *p_impl->get());
}

}