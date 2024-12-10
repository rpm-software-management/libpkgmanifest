#pragma once

#include "imodules.hpp"

#include "impl/common/yaml/iyamlnode.hpp"

#include <memory>

namespace libpkgmanifest::internal::input {

using namespace libpkgmanifest::internal::common;

class IModulesParser {
public:
    virtual ~IModulesParser() = default;

    virtual std::unique_ptr<IModules> parse(const IYamlNode & node) const = 0;
};

}