#include "packagefactory.hpp"

namespace liblockfile {

std::unique_ptr<IPackageInternal> PackageFactory::create() const {
    throw; // TODO: return std::make_unique<Package>();
}   

}