#include "packages.hpp"
#include "packagesfactory.hpp"

namespace libpkgmanifest::internal::manifest {

std::unique_ptr<IPackages> PackagesFactory::create() const {
    return std::make_unique<Packages>();
}   

}