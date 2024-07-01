#pragma once

#include "ipackageinternal.hpp"

#include "liblockfile/yaml/iyamlnode.hpp"

#include <memory>

namespace liblockfile {

class IPackageParser {
public:
    virtual ~IPackageParser() = default;

    virtual std::unique_ptr<IPackageInternal> parse(const std::string & arch, const IYamlNode & node) const = 0;
};

}