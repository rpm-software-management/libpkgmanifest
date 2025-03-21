#pragma once

#include "ipackages.hpp"

#include <map>

namespace libpkgmanifest::internal::manifest {

class PackagesNoSuchArchError : public std::runtime_error {
public:
    PackagesNoSuchArchError(const std::string & message);
};

class Packages : public IPackages {
public:
    Packages();
    Packages(const Packages & other);

    virtual std::unique_ptr<IPackages> clone() const override;

    virtual const std::vector<std::string> get_archs() const override;
    virtual const std::vector<std::unique_ptr<IPackage>> & get(const std::string & arch) const override;

    virtual void add(std::unique_ptr<IPackage> package) override;
    virtual void add(std::unique_ptr<IPackage> package, const std::string & basearch) override;

    virtual bool contains(const IPackage & package) const override;

private:
    IPackage * find(const IPackage & package) const;
    IPackage * find_or_add(std::unique_ptr<IPackage> package);

    std::map<std::string, std::vector<std::unique_ptr<IPackage>>> packages;
};

}