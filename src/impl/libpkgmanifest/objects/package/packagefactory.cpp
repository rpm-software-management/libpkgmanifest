#include "package.hpp"
#include "packagefactory.hpp"

namespace libpkgmanifest::internal {

std::unique_ptr<IPackage> PackageFactory::create() const {
    return std::unique_ptr<IPackage>(new Package());
}   

}