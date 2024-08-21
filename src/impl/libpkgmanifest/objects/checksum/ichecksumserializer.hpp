#pragma once

#include "ichecksum.hpp"

#include "libpkgmanifest/yaml/iyamlnode.hpp"

#include <memory>

namespace libpkgmanifest::internal {

class IChecksumSerializer {
public:
    virtual ~IChecksumSerializer() = default;

    virtual std::unique_ptr<IYamlNode> serialize(const IChecksum & checksum) const = 0;
};

}