#pragma once

#include "liblockfile/ipackages.hpp"
#include "liblockfile/yaml/iyamlnode.hpp"

#include <memory>

namespace liblockfile {

class IPackagesParser {
public:
    virtual ~IPackagesParser() = default;

    virtual std::unique_ptr<IPackages> parse(IYamlNode & node) const = 0;
};

}