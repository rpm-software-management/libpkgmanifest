#pragma once

#include "iversion.hpp"

#include "liblockfile/yaml/iyamlnode.hpp"

#include <memory>

namespace liblockfile {

class IVersionSerializer {
public:
    virtual ~IVersionSerializer() = default;

    virtual std::unique_ptr<IYamlNode> serialize(const IVersion & version) const = 0;
};

}