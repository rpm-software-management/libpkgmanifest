#pragma once

#include "ipackagefactory.hpp"

#include "libpkgmanifest/objects/checksum/ichecksumfactory.hpp"

namespace libpkgmanifest::internal {

class PackageFactory : public IPackageFactory {
public:
    PackageFactory(std::shared_ptr<IChecksumFactory> checksum_factory);

    virtual std::unique_ptr<IPackage> create() const override;

private:
    std::shared_ptr<IChecksumFactory> checksum_factory;
};

}