#include "packages.hpp"

namespace liblockfile::internal {

Packages::Packages() {}

const std::map<std::string, std::vector<std::unique_ptr<IPackage>>> & Packages::get() const {
    return packages;
}

const std::vector<std::unique_ptr<IPackage>> & Packages::get(const std::string &arch) const {
    return packages.at(arch); // TODO: Handle exceptions
}

void Packages::add(std::unique_ptr<IPackage> package) {
    packages[package->get_arch()].push_back(std::move(package));
}

}