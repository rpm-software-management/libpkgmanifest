#pragma once

#include "ipackageinternal.hpp"

#include <memory>

namespace liblockfile::internal {

class IPackageFactory {
public:
    virtual ~IPackageFactory() = default;

    virtual std::unique_ptr<IPackageInternal> create() const = 0;
};

}