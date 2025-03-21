#include "packages.hpp"

#include <algorithm>
#include <ranges>

namespace libpkgmanifest::internal::manifest {

PackagesNoSuchArchError::PackagesNoSuchArchError(const std::string & message)
    : std::runtime_error(message) {}

Packages::Packages() {}

Packages::Packages(const Packages & other) {
    for (const auto & arch_packages : other.packages | std::views::values) {
        for (const auto & package : arch_packages) {
            add(package->clone());
        }
    }
}

std::unique_ptr<IPackages> Packages::clone() const {
    return std::make_unique<Packages>(*this);
}

const std::vector<std::string> Packages::get_archs() const {
    std::vector<std::string> archs;
    std::ranges::copy(packages | std::views::keys, std::back_inserter(archs));
    return archs;
}

const std::vector<std::unique_ptr<IPackage>> & Packages::get(const std::string & arch) const {
    if (packages.find(arch) == packages.end()) {
        throw PackagesNoSuchArchError("No packages for arch: " + arch);
    }
    return packages.at(arch);
}

void Packages::add(std::unique_ptr<IPackage> package) {
    find_or_add(std::move(package));
}

void Packages::add(std::unique_ptr<IPackage> package, const std::string & basearch) {
    auto added_package = find_or_add(std::move(package));
    if (added_package->get_nevra().get_arch() != basearch) {
        added_package->get_parent_archs().push_back(basearch);
    }
}

bool Packages::contains(const IPackage & package) const {
    return find(package) != nullptr;
}

IPackage * Packages::find(const IPackage & package) const {
    auto map_it = packages.find(package.get_nevra().get_arch());
    if (map_it == packages.end()) {
        return nullptr;
    }

    auto & arch_packages = map_it->second;
    auto found_it = std::find_if(arch_packages.begin(), arch_packages.end(), [&](const auto & it_package) {
        return it_package->get_nevra().to_string() == package.get_nevra().to_string() && 
               it_package->get_repo_id() == package.get_repo_id();
    });

    if (found_it != arch_packages.end()) {
        return found_it->get();
    } else {
        return nullptr;
    }
}

IPackage * Packages::find_or_add(std::unique_ptr<IPackage> package) {
    auto result = find(*package);
    if (result != nullptr) {
        return result;
    }

    result = package.get();
    auto arch = package->get_nevra().get_arch();
    packages[arch].push_back(std::move(package));
    return result;
}

}