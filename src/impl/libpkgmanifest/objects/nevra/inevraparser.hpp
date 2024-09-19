#pragma once

#include "inevra.hpp"

#include "libpkgmanifest/yaml/iyamlnode.hpp"

#include <memory>
#include <string>

namespace libpkgmanifest::internal {

class INevraParser {
public:
    virtual ~INevraParser() = default;

    virtual std::unique_ptr<INevra> parse(const IYamlNode & node) const = 0;
    virtual std::unique_ptr<INevra> parse(const std::string & name, const std::string & arch, const IYamlNode & node) const = 0;
};

}