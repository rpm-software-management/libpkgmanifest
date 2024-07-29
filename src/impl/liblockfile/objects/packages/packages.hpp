#pragma once

#include "ipackagesinternal.hpp"

namespace liblockfile::internal {

class Packages : public IPackagesInternal {
public:
    Packages();

    virtual const std::map<std::string, std::vector<std::unique_ptr<IPackage>>> & get() const override;
    virtual const std::vector<std::unique_ptr<IPackage>> & get(const std::string & arch) const override;
    virtual void add(std::unique_ptr<IPackage> package) override;

private:
    std::map<std::string, std::vector<std::unique_ptr<IPackage>>> packages;
};

}