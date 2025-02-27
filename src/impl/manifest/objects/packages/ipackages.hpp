#pragma once

#include "impl/manifest/objects/package/ipackage.hpp"

#include <memory>
#include <string>
#include <vector>

namespace libpkgmanifest::internal::manifest {

class IPackages {
public:
    virtual ~IPackages() = default;

    virtual std::unique_ptr<IPackages> clone() const = 0;

    virtual const std::vector<std::string> get_archs() const = 0;
    virtual const std::vector<std::unique_ptr<IPackage>> & get(const std::string & arch) const = 0;

    virtual void add(std::unique_ptr<IPackage> package) = 0;
    virtual void add(std::unique_ptr<IPackage> package, const std::string & basearch) = 0;

    virtual bool contains(const IPackage & package) const = 0;
};

}