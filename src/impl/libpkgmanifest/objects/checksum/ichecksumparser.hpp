#pragma once

#include "ichecksum.hpp"

#include "libpkgmanifest/yaml/iyamlnode.hpp"

#include <memory>

namespace libpkgmanifest::internal {

class IChecksumParser {
public:
    virtual ~IChecksumParser() = default;

    virtual std::unique_ptr<IChecksum> parse(const IYamlNode & node) const = 0;
};

}