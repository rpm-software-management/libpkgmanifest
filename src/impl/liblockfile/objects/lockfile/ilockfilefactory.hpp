#pragma once

#include "ilockfileinternal.hpp"

#include <memory>

namespace liblockfile::internal {

class ILockFileFactory {
public:
    virtual ~ILockFileFactory() = default;

    virtual std::unique_ptr<ILockFileInternal> create() const = 0;
};

}