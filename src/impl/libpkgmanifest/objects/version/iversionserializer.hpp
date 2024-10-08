#pragma once

#include "iversion.hpp"

#include "impl/libpkgmanifest/yaml/iyamlnode.hpp"

#include <memory>

namespace libpkgmanifest::internal {

class IVersionSerializer {
public:
    virtual ~IVersionSerializer() = default;

    virtual std::unique_ptr<IYamlNode> serialize(const IVersion & version) const = 0;
};

}