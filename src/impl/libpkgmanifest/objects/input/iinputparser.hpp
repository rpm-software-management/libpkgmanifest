#pragma once

#include "iinput.hpp"

#include "impl/libpkgmanifest/yaml/iyamlnode.hpp"

#include <memory>

namespace libpkgmanifest::internal {

class IInputParser {
public:
    virtual ~IInputParser() = default;

    virtual std::unique_ptr<IInput> parse(const IYamlNode & node) const = 0;
};

}