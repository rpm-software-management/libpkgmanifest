#pragma once

#include "imodule.hpp"

#include "impl/common/yaml/iyamlnode.hpp"

#include <memory>

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

class IModuleParser {
public:
    virtual ~IModuleParser() = default;

    virtual std::unique_ptr<IModule> parse(const IYamlNode & node) const = 0;
};

}