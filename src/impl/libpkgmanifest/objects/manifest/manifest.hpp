#pragma once

#include "imanifest.hpp"

#include "libpkgmanifest/operations/ipackagerepositorybinder.hpp"

namespace libpkgmanifest::internal {

class Manifest : public IManifest {
public:
    Manifest();
    Manifest(const Manifest & other);

    virtual std::unique_ptr<IManifest> clone() const override;

    virtual std::string get_document() const override;
    virtual IVersion & get_version() override;
    virtual const IVersion & get_version() const override;
    virtual IPackages & get_packages() override;
    virtual const IPackages & get_packages() const override;
    virtual const IRepositories & get_repositories() const override;
    virtual IRepositories & get_repositories() override;

    virtual void set_document(const std::string & document) override;
    virtual void set_version(std::unique_ptr<IVersion> version) override;
    virtual void set_packages(std::unique_ptr<IPackages> packages) override;
    virtual void set_repositories(std::unique_ptr<IRepositories> repositories) override;

    void set_package_repository_binder(std::shared_ptr<IPackageRepositoryBinder> binder);

private:
    std::string document;
    std::unique_ptr<IVersion> version;
    std::unique_ptr<IPackages> packages;
    std::unique_ptr<IRepositories> repositories;
    std::shared_ptr<IPackageRepositoryBinder> binder;
};

}