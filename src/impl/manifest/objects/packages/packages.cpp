#include "packages.hpp"

#include <algorithm>

namespace libpkgmanifest::internal::manifest {

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
    packages[package->get_nevra().get_arch()].push_back(std::move(package));
}

bool Packages::contains(const IPackage & package) const {
    auto map_it = packages.find(package.get_nevra().get_arch());
    if (map_it == packages.end()) {
        return false;
    }

    auto & arch_packages = map_it->second;
    auto found_it = std::find_if(arch_packages.begin(), arch_packages.end(), [&](const std::unique_ptr<IPackage> & it_package) {
        return it_package->get_nevra().to_string() == package.get_nevra().to_string() && 
               it_package->get_repo_id() == package.get_repo_id();
    });

    return found_it != arch_packages.end();
}

}