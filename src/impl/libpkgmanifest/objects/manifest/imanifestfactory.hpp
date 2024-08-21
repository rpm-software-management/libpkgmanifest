#pragma once

#include "imanifest.hpp"

#include <memory>

namespace libpkgmanifest::internal {

class IManifestFactory {
public:
    virtual ~IManifestFactory() = default;

    virtual std::unique_ptr<IManifest> create() const = 0;
};

}