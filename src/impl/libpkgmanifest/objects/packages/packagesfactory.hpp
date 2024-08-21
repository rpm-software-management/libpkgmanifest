#pragma once

#include "ipackagesfactory.hpp"

namespace libpkgmanifest::internal {

class PackagesFactory : public IPackagesFactory {
public:
    virtual std::unique_ptr<IPackages> create() const override;
};

}