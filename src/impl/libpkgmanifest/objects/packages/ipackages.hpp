#pragma once

#include "impl/libpkgmanifest/objects/package/ipackage.hpp"

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace libpkgmanifest::internal {

class IPackages {
public:
    virtual ~IPackages() = default;

    virtual std::unique_ptr<IPackages> clone() const = 0;

    virtual const std::map<std::string, std::vector<std::unique_ptr<IPackage>>> & get() const = 0;
    virtual std::map<std::string, std::vector<std::unique_ptr<IPackage>>> & get() = 0;

    virtual void add(std::unique_ptr<IPackage> package) = 0;
    virtual bool contains(const IPackage & package) const = 0;
};

}