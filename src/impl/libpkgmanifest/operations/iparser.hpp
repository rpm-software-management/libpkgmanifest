#pragma once

#include "impl/libpkgmanifest/objects/manifest/imanifest.hpp"

#include <memory>
#include <string>

namespace libpkgmanifest::internal {

class IParser {
public:
    virtual ~IParser() = default;

    virtual std::unique_ptr<IManifest> parse(const std::string & path) const = 0;
};

}