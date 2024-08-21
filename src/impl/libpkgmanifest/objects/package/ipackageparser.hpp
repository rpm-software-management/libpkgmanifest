#pragma once

#include "ipackage.hpp"

#include "libpkgmanifest/yaml/iyamlnode.hpp"

#include <memory>

namespace libpkgmanifest::internal {

class IPackageParser {
public:
    virtual ~IPackageParser() = default;

    virtual std::unique_ptr<IPackage> parse(const std::string & arch, const IYamlNode & node) const = 0;
};

}