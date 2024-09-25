#pragma once

#include "ipackagefactory.hpp"

#include "libpkgmanifest/objects/checksum/ichecksumfactory.hpp"
#include "libpkgmanifest/objects/module/imodulefactory.hpp"
#include "libpkgmanifest/objects/nevra/inevrafactory.hpp"

namespace libpkgmanifest::internal {

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