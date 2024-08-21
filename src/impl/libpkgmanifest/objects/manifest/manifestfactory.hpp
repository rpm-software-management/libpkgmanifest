#pragma once

#include "imanifestfactory.hpp"

namespace libpkgmanifest::internal {

class ManifestFactory : public IManifestFactory {
public:
    virtual std::unique_ptr<IManifest> create() const override;
};

}