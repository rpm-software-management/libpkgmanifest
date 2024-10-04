#pragma once

#include "libpkgmanifest/objects/package/ipackage.hpp"
#include "libpkgmanifest/objects/packages/ipackages.hpp"
#include "libpkgmanifest/objects/repositories/irepositories.hpp"

namespace libpkgmanifest::internal {

class IPackageRepositoryBinder {
public:
    virtual ~IPackageRepositoryBinder() = default;

    virtual void validate(const IRepositories & repositories, const IPackage & package) const = 0;
    virtual void validate(const IRepositories & repositories, const IPackages & packages) const = 0;
    virtual void bind(const IRepositories & repositories, IPackage & package) = 0;
    virtual void bind(const IRepositories & repositories, IPackages & packages) = 0;
};

}