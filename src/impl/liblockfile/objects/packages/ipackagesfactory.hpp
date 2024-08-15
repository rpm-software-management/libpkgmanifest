#pragma once

#include "ipackages.hpp"

#include <memory>

namespace liblockfile::internal {

class IPackagesFactory {
public:
    virtual ~IPackagesFactory() = default;

    virtual std::unique_ptr<IPackages> create() const = 0;
};

}