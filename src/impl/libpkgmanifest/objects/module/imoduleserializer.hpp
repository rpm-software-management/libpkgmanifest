#pragma once

#include "imodule.hpp"

#include "libpkgmanifest/yaml/iyamlnode.hpp"

#include <memory>

namespace libpkgmanifest::internal {

class IModuleSerializer {
public:
    virtual ~IModuleSerializer() = default;

    virtual std::unique_ptr<IYamlNode> serialize(const IModule & version) const = 0;
};

}