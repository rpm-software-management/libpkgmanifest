#pragma once

#include "iversioninternal.hpp"

#include <memory>

namespace liblockfile::internal {

class IVersionFactory {
public:
    virtual ~IVersionFactory() = default;

    virtual std::unique_ptr<IVersionInternal> create() const = 0;
};

}