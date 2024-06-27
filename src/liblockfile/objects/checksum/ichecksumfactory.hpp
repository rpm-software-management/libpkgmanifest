#pragma once

#include "ichecksuminternal.hpp"

#include <memory>

namespace liblockfile {

class IChecksumFactory {
public:
    virtual ~IChecksumFactory() = default;

    virtual std::unique_ptr<IChecksumInternal> create() const = 0;
};

}