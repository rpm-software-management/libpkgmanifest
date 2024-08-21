#pragma once

#include "imanifest.hpp"

#include "libpkgmanifest/yaml/iyamlnode.hpp"

#include <memory>

namespace libpkgmanifest::internal {

class IManifestParser {
public:
    virtual ~IManifestParser() = default;

    virtual std::unique_ptr<IManifest> parse(const IYamlNode & node) const = 0;
};

}