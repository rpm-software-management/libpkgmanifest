#pragma once

#include "impl/manifest/objects/packages/ipackages.hpp"
#include "impl/common/objects/repositories/irepositories.hpp"
#include "impl/common/objects/version/iversion.hpp"

#include <memory>
#include <string>

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

class IManifest {
public:
    virtual ~IManifest() = default;

    virtual std::unique_ptr<IManifest> clone() const = 0;

    virtual std::string get_document() const = 0;
    virtual const IVersion & get_version() const = 0;
    virtual IVersion & get_version() = 0;
    virtual const IPackages & get_packages() const = 0;
    virtual IPackages & get_packages() = 0;
    virtual const IRepositories & get_repositories() const = 0;
    virtual IRepositories & get_repositories() = 0;

    virtual void set_document(const std::string & document) = 0;
    virtual void set_version(std::unique_ptr<IVersion> version) = 0;
    virtual void set_packages(std::unique_ptr<IPackages> packages) = 0;
    virtual void set_repositories(std::unique_ptr<IRepositories> repositories) = 0;
};

}