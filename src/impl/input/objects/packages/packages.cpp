#include "packages.hpp"

namespace libpkgmanifest::internal::input {

Packages::Packages()
    : installs()
    , reinstalls() {}

std::unique_ptr<IPackages> Packages::clone() const {
    return std::unique_ptr<IPackages>(new Packages(*this));
}

const std::vector<std::string> & Packages::get_installs() const {
    return installs;
}

std::vector<std::string> & Packages::get_installs() {
    return installs;
}

const std::vector<std::string> & Packages::get_reinstalls() const {
    return reinstalls;
}

std::vector<std::string> & Packages::get_reinstalls() {
    return reinstalls;
}

}
