#pragma once

#include "iyamlnode.hpp"

#include <memory>
#include <string>

namespace libpkgmanifest::internal::common {

class IYamlParser {
public:
    virtual ~IYamlParser() = default;

    virtual std::unique_ptr<IYamlNode> from_string(const std::string & yaml) const = 0;
    virtual std::unique_ptr<IYamlNode> from_file(const std::string & path) const = 0;
};

}