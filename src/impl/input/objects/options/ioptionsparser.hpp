#pragma once

#include "ioptions.hpp"

#include "impl/common/yaml/iyamlnode.hpp"

#include <memory>

namespace libpkgmanifest::internal::input {

using namespace libpkgmanifest::internal::common;

class IOptionsParser {
public:
    virtual ~IOptionsParser() = default;

    virtual std::unique_ptr<IOptions> parse(const IYamlNode & node) const = 0;
};

}