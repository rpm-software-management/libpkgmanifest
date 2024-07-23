#pragma once

#include "liblockfile/ichecksum.hpp"

#include "liblockfile/yaml/iyamlnode.hpp"

#include <memory>

namespace liblockfile {

class IChecksumSerializer {
public:
    virtual ~IChecksumSerializer() = default;

    virtual std::unique_ptr<IYamlNode> serialize(const IChecksum & checksum) const = 0;
};

}