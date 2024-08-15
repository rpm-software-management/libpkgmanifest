#pragma once

#include "ichecksumfactory.hpp"

namespace liblockfile::internal {

class ChecksumFactory : public IChecksumFactory {
public:
    virtual std::unique_ptr<IChecksum> create() const override;
};

}