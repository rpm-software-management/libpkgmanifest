#include "package.hpp"
#include "packagefactory.hpp"

namespace libpkgmanifest::internal {

PackageFactory::PackageFactory(std::shared_ptr<IChecksumFactory> checksum_factory)
    : checksum_factory(checksum_factory) {}

std::unique_ptr<IPackage> PackageFactory::create() const {
    auto package = std::make_unique<Package>();
    package->set_checksum(checksum_factory->create());
    return package;
}   

}