#pragma once

#include "ipackages.hpp"

#include "libpkgmanifest/yaml/iyamlnode.hpp"

#include <memory>

namespace libpkgmanifest::internal {

class IPackagesParser {
public:
    virtual ~IPackagesParser() = default;

    virtual std::unique_ptr<IPackages> parse(const IYamlNode & node) const = 0;
};

}