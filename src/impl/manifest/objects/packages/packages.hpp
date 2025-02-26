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
    virtual const std::vector<std::reference_wrapper<IPackage>> & get_noarch(const std::string & basearch) const override;
    virtual void add(std::unique_ptr<IPackage> package) override;
    virtual void add(std::unique_ptr<IPackage> package, const std::string & basearch) override;

    virtual bool contains(const IPackage & package) const override;

private:
    void link(IPackage & package, const std::string & basearch);

    std::map<std::string, std::vector<std::unique_ptr<IPackage>>> packages;
    std::map<std::string, std::vector<std::reference_wrapper<IPackage>>> noarch_packages;
};

}