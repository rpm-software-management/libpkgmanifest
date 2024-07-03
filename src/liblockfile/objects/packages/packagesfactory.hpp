#pragma once

#include "ipackagesfactory.hpp"

namespace liblockfile {

class PackagesFactory : public IPackagesFactory {
public:
    virtual std::unique_ptr<IPackagesInternal> create() const override;
};

}