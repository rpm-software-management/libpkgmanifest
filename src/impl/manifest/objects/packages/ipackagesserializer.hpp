#pragma once

#include "ipackages.hpp"

#include "impl/common/yaml/iyamlnode.hpp"

#include <memory>

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

class IPackagesSerializer {
public:
    virtual ~IPackagesSerializer() = default;

    virtual std::unique_ptr<IYamlNode> serialize(const IPackages & packages) const = 0;
};

}