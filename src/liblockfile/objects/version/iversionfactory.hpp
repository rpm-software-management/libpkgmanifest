#pragma once

#include "iversioninternal.hpp"

#include <memory>

namespace liblockfile {

class IVersionFactory {
public:
    virtual ~IVersionFactory() = default;

    virtual std::unique_ptr<IVersionInternal> create() const = 0;
};

}