#pragma once

#include "impl/common/yaml/iyamlnode.hpp"

#include <string>
#include <vector>

namespace libpkgmanifest::internal::common {

class IStringListParser {
public:
    virtual ~IStringListParser() = default;

    virtual std::vector<std::string> parse(const IYamlNode & node) const = 0;
};

}