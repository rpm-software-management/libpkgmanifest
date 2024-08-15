#pragma once

#include "ipackagesfactory.hpp"

namespace liblockfile::internal {

class PackagesFactory : public IPackagesFactory {
public:
    virtual std::unique_ptr<IPackages> create() const override;
};

}