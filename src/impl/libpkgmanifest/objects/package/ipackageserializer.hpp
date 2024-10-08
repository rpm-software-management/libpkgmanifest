#pragma once

#include "ipackage.hpp"

#include "impl/libpkgmanifest/yaml/iyamlnode.hpp"

#include <memory>

namespace libpkgmanifest::internal {

class IPackageSerializer {
public:
    virtual ~IPackageSerializer() = default;

    virtual std::unique_ptr<IYamlNode> serialize(const IPackage & package) const = 0;
};

}