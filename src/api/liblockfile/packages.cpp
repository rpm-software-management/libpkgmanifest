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

std::map<std::string, std::vector<Package>> Packages::get() const {
    std::map<std::string, std::vector<Package>> packages_map;
    for (auto & [arch, internal_arch_packages] : p_impl->get()->get()) {
        std::vector<Package> arch_packages;
        arch_packages.reserve(internal_arch_packages.size());
        for (auto & internal_package : internal_arch_packages) {
            Package package;
            package.p_impl->from_internal(internal_package.get());
            arch_packages.push_back(std::move(package));
        }
        packages_map.insert({arch, std::move(arch_packages)});
    }
    return packages_map;
}

std::vector<Package> Packages::get(const std::string & arch) const {
    std::vector<Package> packages;
    auto & internal_packages = p_impl->get()->get()[arch];
    packages.reserve(internal_packages.size());
    for (auto & internal_package : internal_packages) {
        Package package;
        package.p_impl->from_internal(internal_package.get());
        packages.push_back(std::move(package));
    }
    return packages;
}

void Packages::add(Package & package) {
    p_impl->get()->add(package.p_impl->get_factory_object());
}

}