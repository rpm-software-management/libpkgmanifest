#pragma once

#include "ipackage.hpp"

#include <memory>

namespace liblockfile::internal {

class IPackageFactory {
public:
    virtual ~IPackageFactory() = default;

    virtual std::unique_ptr<IPackage> create() const = 0;
};

}