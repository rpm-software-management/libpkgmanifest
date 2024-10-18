#pragma once

#include "impl/libpkgmanifest/yaml/iyamlnode.hpp"

#include <memory>

namespace libpkgmanifest::internal {

class IPrototypeInFileConverter {
public:
    virtual ~IPrototypeInFileConverter() = default;

    virtual std::unique_ptr<IYamlNode> convert(const IYamlNode & node) const = 0;
};

}