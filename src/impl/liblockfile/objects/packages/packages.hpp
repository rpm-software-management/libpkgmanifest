#pragma once

#include "ipackages.hpp"

namespace liblockfile::internal {

class Packages : public IPackages {
public:
    Packages();
    Packages(const Packages & other);

    virtual std::unique_ptr<IPackages> clone() const override;

    virtual std::map<std::string, std::vector<std::unique_ptr<IPackage>>> & get() override;
    virtual const std::map<std::string, std::vector<std::unique_ptr<IPackage>>> & get() const override;
    virtual void add(std::unique_ptr<IPackage> package) override;

private:
    std::map<std::string, std::vector<std::unique_ptr<IPackage>>> packages;
};

}