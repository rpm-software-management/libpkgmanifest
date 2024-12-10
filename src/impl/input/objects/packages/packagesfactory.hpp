#pragma once

#include "ipackagesfactory.hpp"

namespace libpkgmanifest::internal::input {

class PackagesFactory : public IPackagesFactory {
public:
    virtual std::unique_ptr<IPackages> create() const override;
};

}