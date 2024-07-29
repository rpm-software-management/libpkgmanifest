#pragma once

#include "ipackagesfactory.hpp"

namespace liblockfile::internal {

class PackagesFactory : public IPackagesFactory {
public:
    virtual std::unique_ptr<IPackagesInternal> create() const override;
};

}