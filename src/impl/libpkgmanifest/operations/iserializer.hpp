#pragma once

#include "impl/libpkgmanifest/objects/manifest/imanifest.hpp"

#include <string>

namespace libpkgmanifest::internal {

class ISerializer {
public:
    virtual ~ISerializer() = default;

    virtual void serialize(const IManifest & manifest, const std::string & path) const = 0;
};

}