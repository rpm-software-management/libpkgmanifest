#include "packages.hpp"
#include "packagesfactory.hpp"

namespace liblockfile {

std::unique_ptr<IPackagesInternal> PackagesFactory::create() const {
    return std::unique_ptr<IPackagesInternal>(new Packages());
}   

}