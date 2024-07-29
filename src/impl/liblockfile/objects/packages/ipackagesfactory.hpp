#pragma once

#include "ipackagesinternal.hpp"

#include <memory>

namespace liblockfile::internal {

class IPackagesFactory {
public:
    virtual ~IPackagesFactory() = default;

    virtual std::unique_ptr<IPackagesInternal> create() const = 0;
};

}