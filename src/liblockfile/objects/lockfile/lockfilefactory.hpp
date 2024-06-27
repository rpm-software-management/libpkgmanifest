#pragma once

#include "ilockfilefactory.hpp"

namespace liblockfile {

class LockFileFactory : ILockFileFactory {
public:
    virtual std::unique_ptr<ILockFileInternal> create() const override;
};

}