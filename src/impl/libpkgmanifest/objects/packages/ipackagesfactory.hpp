#pragma once

#include "ipackages.hpp"

#include <memory>

namespace libpkgmanifest::internal {

class IPackagesFactory {
public:
    virtual ~IPackagesFactory() = default;

    virtual std::unique_ptr<IPackages> create() const = 0;
};

}