#include "packages.hpp"

namespace liblockfile {

const std::vector<std::unique_ptr<IPackage>> & Packages::get_by_arch([[maybe_unused]] const std::string &arch) const {
    return packages;
}

const std::vector<std::unique_ptr<IPackage>> & Packages::get() const {
    return packages;
}

void Packages::add_package([[maybe_unused]] std::unique_ptr<IPackage> package) {
    throw; // TODO
}

}