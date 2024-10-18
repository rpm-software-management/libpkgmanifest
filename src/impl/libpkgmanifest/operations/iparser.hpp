#pragma once

#include "impl/libpkgmanifest/objects/input/iinput.hpp"
#include "impl/libpkgmanifest/objects/manifest/imanifest.hpp"

#include <memory>
#include <string>

namespace libpkgmanifest::internal {

class IParser {
public:
    virtual ~IParser() = default;

    virtual std::unique_ptr<IInput> parse_input(const std::string & path) const = 0;
    virtual std::unique_ptr<IInput> parse_input_from_prototype(const std::string & path) const = 0;
    virtual std::unique_ptr<IManifest> parse_manifest(const std::string & path) const = 0;
};

}