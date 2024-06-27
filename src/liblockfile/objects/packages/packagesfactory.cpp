#include "packagesfactory.hpp"

namespace liblockfile {

std::unique_ptr<IPackagesInternal> PackagesFactory::create() const {
    throw; // TODO: return std::make_unique<Packages>();
}   

}