#pragma once

#include "inevrafactory.hpp"

namespace libpkgmanifest::internal {

class NevraFactory : public INevraFactory {
public:
    virtual std::unique_ptr<INevra> create() const override;
};

}