#pragma once

#include "ipackagerepositorybinder.hpp"

#include "impl/common/objects/repository/irepository.hpp"

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

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