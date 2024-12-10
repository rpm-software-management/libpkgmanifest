#pragma once

#include "ipackages.hpp"

#include "impl/common/yaml/iyamlnode.hpp"

#include <memory>

namespace libpkgmanifest::internal::input {

using namespace libpkgmanifest::internal::common;

class IPackagesParser {
public:
    virtual ~IPackagesParser() = default;

    virtual std::unique_ptr<IPackages> parse(const IYamlNode & node) const = 0;
};

}