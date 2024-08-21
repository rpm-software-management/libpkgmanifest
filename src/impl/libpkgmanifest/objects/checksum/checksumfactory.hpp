#pragma once

#include "ichecksumfactory.hpp"

namespace libpkgmanifest::internal {

class ChecksumFactory : public IChecksumFactory {
public:
    virtual std::unique_ptr<IChecksum> create() const override;
};

}