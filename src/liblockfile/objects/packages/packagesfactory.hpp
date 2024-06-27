#pragma once

#include "ipackagesfactory.hpp"

namespace liblockfile {

class PackagesFactory : IPackagesFactory {
public:
    virtual std::unique_ptr<IPackagesInternal> create() const override;
};

}