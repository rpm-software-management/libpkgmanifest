#pragma once

#include "ichecksum.hpp"

#include "impl/common/yaml/iyamlnode.hpp"

#include <memory>

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

class IChecksumSerializer {
public:
    virtual ~IChecksumSerializer() = default;

    virtual std::unique_ptr<IYamlNode> serialize(const IChecksum & checksum) const = 0;
};

}