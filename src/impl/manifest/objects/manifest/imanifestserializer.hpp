#pragma once

#include "imanifest.hpp"

#include "impl/common/yaml/iyamlnode.hpp"

#include <memory>

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

class IManifestSerializer {
public:
    virtual ~IManifestSerializer() = default;

    virtual std::unique_ptr<IYamlNode> serialize(const IManifest & manifest) const = 0;
};

}