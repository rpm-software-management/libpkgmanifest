#pragma once

#include "impl/common/yaml/iyamlnode.hpp"

#include <memory>

namespace libpkgmanifest::internal::input {

using namespace libpkgmanifest::internal::common;

class IPrototypeFileConverter {
public:
    virtual ~IPrototypeFileConverter() = default;

    virtual std::unique_ptr<IYamlNode> convert(const IYamlNode & node) const = 0;
};

}