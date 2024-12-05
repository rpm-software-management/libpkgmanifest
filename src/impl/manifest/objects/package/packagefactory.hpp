#pragma once

#include "ipackagefactory.hpp"

#include "impl/manifest/objects/checksum/ichecksumfactory.hpp"
#include "impl/manifest/objects/module/imodulefactory.hpp"
#include "impl/manifest/objects/nevra/inevrafactory.hpp"

namespace libpkgmanifest::internal::manifest {

class PackageFactory : public IPackageFactory {
public:
    PackageFactory(
        std::shared_ptr<IChecksumFactory> checksum_factory,
        std::shared_ptr<INevraFactory> nevra_factory,
        std::shared_ptr<IModuleFactory> module_factory);

    virtual std::unique_ptr<IPackage> create() const override;

private:
    std::shared_ptr<IChecksumFactory> checksum_factory;
    std::shared_ptr<INevraFactory> nevra_factory;
    std::shared_ptr<IModuleFactory> module_factory;
};

}