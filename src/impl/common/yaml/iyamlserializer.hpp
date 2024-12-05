#pragma once

#include "iyamlnode.hpp"

#include <string>

namespace libpkgmanifest::internal::common {

class IYamlSerializer {
public:
    virtual ~IYamlSerializer() = default;

    virtual std::string to_string(const IYamlNode & node) const = 0;
    virtual void to_file(const IYamlNode & node, const std::string & path) const = 0;
};

}