#pragma once

#include "imanifest.hpp"

#include "impl/common/yaml/iyamlnode.hpp"

#include <memory>

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

class IManifestParser {
public:
    virtual ~IManifestParser() = default;

    virtual std::unique_ptr<IManifest> parse(const IYamlNode & node) const = 0;
};

}