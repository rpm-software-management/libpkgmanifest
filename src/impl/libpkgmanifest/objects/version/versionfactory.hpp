#pragma once

#include "iversionfactory.hpp"

namespace libpkgmanifest::internal {

class VersionFactory : public IVersionFactory {
public:
    virtual std::unique_ptr<IVersion> create() const override;
};

}