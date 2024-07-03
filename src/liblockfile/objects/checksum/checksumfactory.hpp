#pragma once

#include "ichecksumfactory.hpp"

namespace liblockfile {

class ChecksumFactory : public IChecksumFactory {
public:
    virtual std::unique_ptr<IChecksumInternal> create() const override;
};

}