#pragma once

#include "ichecksum.hpp"

#include <memory>

namespace libpkgmanifest::internal::manifest {

class IChecksumFactory {
public:
    virtual ~IChecksumFactory() = default;

    virtual std::unique_ptr<IChecksum> create() const = 0;
};

}