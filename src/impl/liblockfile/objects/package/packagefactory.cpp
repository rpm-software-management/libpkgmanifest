#include "package.hpp"
#include "packagefactory.hpp"

namespace liblockfile::internal {

std::unique_ptr<IPackageInternal> PackageFactory::create() const {
    return std::unique_ptr<IPackageInternal>(new Package());
}   

}