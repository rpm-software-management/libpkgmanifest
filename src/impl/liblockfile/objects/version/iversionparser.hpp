#pragma once

#include "iversioninternal.hpp"

#include "liblockfile/yaml/iyamlnode.hpp"

#include <memory>

namespace liblockfile::internal {

class IVersionParser {
public:
    virtual ~IVersionParser() = default;

    virtual std::unique_ptr<IVersionInternal> parse(const IYamlNode & node) const = 0;
};

}