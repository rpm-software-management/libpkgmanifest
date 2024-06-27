#pragma once

#include "liblockfile/ichecksum.hpp"
#include "liblockfile/yaml/iyamlnode.hpp"

#include <memory>

namespace liblockfile {

class IChecksumParser {
public:
    virtual ~IChecksumParser() = default;

    virtual std::unique_ptr<IChecksum> parse(IYamlNode & node) const = 0;
};

}