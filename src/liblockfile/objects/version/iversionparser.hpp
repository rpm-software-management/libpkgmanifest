#pragma once

#include "liblockfile/iversion.hpp"
#include "liblockfile/yaml/iyamlnode.hpp"

#include <memory>

namespace liblockfile {

class IVersionParser {
public:
    virtual ~IVersionParser() = default;

    virtual std::unique_ptr<IVersion> parse(IYamlNode & node) const = 0;
};

}