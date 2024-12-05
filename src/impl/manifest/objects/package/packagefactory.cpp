#include "package.hpp"
#include "packagefactory.hpp"

namespace libpkgmanifest::internal::manifest {

PackageFactory::PackageFactory(
    std::shared_ptr<IChecksumFactory> checksum_factory,
    std::shared_ptr<INevraFactory> nevra_factory,
    std::shared_ptr<IModuleFactory> module_factory)
    : checksum_factory(checksum_factory)
    , nevra_factory(nevra_factory)
    , module_factory(module_factory) {}

std::unique_ptr<IPackage> PackageFactory::create() const {
    auto package = std::make_unique<Package>();
    package->set_checksum(checksum_factory->create());
    package->set_nevra(nevra_factory->create());
    package->set_srpm(nevra_factory->create());
    package->set_module(module_factory->create());
    return package;
}   

}