#pragma once

#include "ichecksum.hpp"

#include <memory>

namespace liblockfile::internal {

class IChecksumFactory {
public:
    virtual ~IChecksumFactory() = default;

    virtual std::unique_ptr<IChecksum> create() const = 0;
};

}