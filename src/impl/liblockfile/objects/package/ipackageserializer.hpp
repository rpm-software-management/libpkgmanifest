#pragma once

#include "ipackage.hpp"

#include "liblockfile/yaml/iyamlnode.hpp"

#include <memory>

namespace liblockfile::internal {

class IPackageSerializer {
public:
    virtual ~IPackageSerializer() = default;

    virtual std::unique_ptr<IYamlNode> serialize(const IPackage & package) const = 0;
};

}