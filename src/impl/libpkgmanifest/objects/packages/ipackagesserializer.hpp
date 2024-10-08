#pragma once

#include "ipackages.hpp"

#include "impl/libpkgmanifest/yaml/iyamlnode.hpp"

#include <memory>

namespace libpkgmanifest::internal {

class IPackagesSerializer {
public:
    virtual ~IPackagesSerializer() = default;

    virtual std::unique_ptr<IYamlNode> serialize(const IPackages & packages) const = 0;
};

}