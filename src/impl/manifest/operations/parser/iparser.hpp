#pragma once

#include "impl/manifest/objects/manifest/imanifest.hpp"

#include <memory>
#include <string>

namespace libpkgmanifest::internal::manifest {

class IParser {
public:
    virtual ~IParser() = default;

    virtual std::unique_ptr<IManifest> parse(const std::string & path) const = 0;
};

}