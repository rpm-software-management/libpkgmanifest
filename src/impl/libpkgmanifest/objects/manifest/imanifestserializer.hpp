#pragma once

#include "imanifest.hpp"

#include "libpkgmanifest/yaml/iyamlnode.hpp"

#include <memory>

namespace libpkgmanifest::internal {

class IManifestSerializer {
public:
    virtual ~IManifestSerializer() = default;

    virtual std::unique_ptr<IYamlNode> serialize(const IManifest & manifest) const = 0;
};

}