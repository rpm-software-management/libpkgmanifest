#pragma once

#include "ipackagerepositorybinder.hpp"

#include "libpkgmanifest/objects/repository/irepository.hpp"

namespace libpkgmanifest::internal {

class PackageRepositoryBinderIdNotFoundError : public std::runtime_error {
public:
    PackageRepositoryBinderIdNotFoundError(const std::string & message);
};

class PackageRepositoryBinder : public IPackageRepositoryBinder {
public:
    PackageRepositoryBinder();

    virtual void validate(const IRepositories & repositories, const IPackage & package) const override;
    virtual void validate(const IRepositories & repositories, const IPackages & packages) const override;
    virtual void bind(const IRepositories & repositories, IPackage & package) override;
    virtual void bind(const IRepositories & repositories, IPackages & packages) override;

private:
    IRepository & get(const IRepositories & repositories, const IPackage & package) const;
};

}