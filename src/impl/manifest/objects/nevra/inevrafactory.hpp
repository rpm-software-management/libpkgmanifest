#pragma once

#include "inevra.hpp"

#include <memory>

namespace libpkgmanifest::internal::manifest {

class INevraFactory {
public:
    virtual ~INevraFactory() = default;

    virtual std::unique_ptr<INevra> create() const = 0;
};

}