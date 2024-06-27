#pragma once

#include "ipackagesinternal.hpp"

namespace liblockfile {

class Packages : IPackagesInternal {
public:
    virtual const std::vector<std::unique_ptr<IPackage>> & get_by_arch(const std::string & arch) const override;
    virtual const std::vector<std::unique_ptr<IPackage>> & get() const override;

    virtual void add_package(std::unique_ptr<IPackage> package) override;

private:
    std::vector<std::unique_ptr<IPackage>> packages;
};

}