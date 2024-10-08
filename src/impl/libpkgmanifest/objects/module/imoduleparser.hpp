#pragma once

#include "imodule.hpp"

#include "impl/libpkgmanifest/yaml/iyamlnode.hpp"

#include <memory>

namespace libpkgmanifest::internal {

class IModuleParser {
public:
    virtual ~IModuleParser() = default;

    virtual std::unique_ptr<IModule> parse(const IYamlNode & node) const = 0;
};

}