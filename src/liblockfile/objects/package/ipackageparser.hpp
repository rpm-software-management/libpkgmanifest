#pragma once

#include "liblockfile/ipackage.hpp"
#include "liblockfile/yaml/iyamlnode.hpp"

#include <memory>

namespace liblockfile {

class IPackageParser {
public:
    virtual ~IPackageParser() = default;

    virtual std::unique_ptr<IPackage> parse(IYamlNode & node) const = 0;
};

}