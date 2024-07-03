#pragma once

#include "ipackagefactory.hpp"

namespace liblockfile {

class PackageFactory : public IPackageFactory {
public:
    virtual std::unique_ptr<IPackageInternal> create() const override;
};

}