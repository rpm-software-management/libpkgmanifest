#pragma once

#include "iversion.hpp"

#include "impl/common/yaml/iyamlnode.hpp"

#include <memory>

namespace libpkgmanifest::internal::common {

class IVersionParser {
public:
    virtual ~IVersionParser() = default;

    virtual std::unique_ptr<IVersion> parse(const IYamlNode & node) const = 0;
};

}