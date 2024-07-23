#pragma once

#include "liblockfile/ipackages.hpp"

#include "liblockfile/yaml/iyamlnode.hpp"

#include <memory>

namespace liblockfile {

class IPackagesSerializer {
public:
    virtual ~IPackagesSerializer() = default;

    virtual std::unique_ptr<IYamlNode> serialize(const IPackages & packages) const = 0;
};

}