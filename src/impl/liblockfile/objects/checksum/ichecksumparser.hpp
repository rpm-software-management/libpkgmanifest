#pragma once

#include "ichecksum.hpp"

#include "liblockfile/yaml/iyamlnode.hpp"

#include <memory>

namespace liblockfile::internal {

class IChecksumParser {
public:
    virtual ~IChecksumParser() = default;

    virtual std::unique_ptr<IChecksum> parse(const IYamlNode & node) const = 0;
};

}