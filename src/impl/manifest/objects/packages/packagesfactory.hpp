#pragma once

#include "ipackagesfactory.hpp"

namespace libpkgmanifest::internal::manifest {

class PackagesFactory : public IPackagesFactory {
public:
    virtual std::unique_ptr<IPackages> create() const override;
};

}