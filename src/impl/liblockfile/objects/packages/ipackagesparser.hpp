#pragma once

#include "ipackagesinternal.hpp"

#include "liblockfile/yaml/iyamlnode.hpp"

#include <memory>

namespace liblockfile::internal {

class IPackagesParser {
public:
    virtual ~IPackagesParser() = default;

    virtual std::unique_ptr<IPackagesInternal> parse(const IYamlNode & node) const = 0;
};

}