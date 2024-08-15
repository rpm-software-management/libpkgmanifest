#include "packages.hpp"

namespace liblockfile::internal {

Packages::Packages() {}

Packages::Packages(const Packages & other) {
    for (const auto & [arch, arch_packages] : other.packages) {
        std::vector<std::unique_ptr<IPackage>> new_arch_packages;
        new_arch_packages.reserve(arch_packages.size());
        for (const auto & package : arch_packages) {
            new_arch_packages.push_back(std::unique_ptr<IPackage>(package->clone()));
        }
        packages.insert({arch, std::move(new_arch_packages)});
    }
}

std::unique_ptr<IPackages> Packages::clone() const {
    return std::unique_ptr<IPackages>(new Packages(*this));
}

const std::map<std::string, std::vector<std::unique_ptr<IPackage>>> & Packages::get() const {
    return packages;
}

std::map<std::string, std::vector<std::unique_ptr<IPackage>>> & Packages::get() {
    return packages;
}

void Packages::add(std::unique_ptr<IPackage> package) {
    packages[package->get_arch()].push_back(std::move(package));
}

}