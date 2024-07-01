#pragma once

#include "ilockfileinternal.hpp"

#include "liblockfile/yaml/iyamlnode.hpp"

#include <memory>

namespace liblockfile {

class ILockFileParser {
public:
    virtual ~ILockFileParser() = default;

    virtual std::unique_ptr<ILockFileInternal> parse(const IYamlNode & node) const = 0;
};

}