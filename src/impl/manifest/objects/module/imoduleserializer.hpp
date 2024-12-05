#pragma once

#include "imodule.hpp"

#include "impl/common/yaml/iyamlnode.hpp"

#include <memory>

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

class IModuleSerializer {
public:
    virtual ~IModuleSerializer() = default;

    virtual std::unique_ptr<IYamlNode> serialize(const IModule & version) const = 0;
};

}