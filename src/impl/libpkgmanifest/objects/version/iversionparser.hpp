#pragma once

#include "iversion.hpp"

#include "libpkgmanifest/yaml/iyamlnode.hpp"

#include <memory>

namespace libpkgmanifest::internal {

class IVersionParser {
public:
    virtual ~IVersionParser() = default;

    virtual std::unique_ptr<IVersion> parse(const IYamlNode & node) const = 0;
};

}