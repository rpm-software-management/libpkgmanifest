#include "packages.hpp"
#include "packagesfactory.hpp"

namespace liblockfile::internal {

std::unique_ptr<IPackages> PackagesFactory::create() const {
    return std::unique_ptr<IPackages>(new Packages());
}   

}