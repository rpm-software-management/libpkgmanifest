#pragma once

#include "ichecksum.hpp"

#include "impl/common/yaml/iyamlnode.hpp"

#include <memory>

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

class IChecksumParser {
public:
    virtual ~IChecksumParser() = default;

    virtual std::unique_ptr<IChecksum> parse(const IYamlNode & node) const = 0;
};

}