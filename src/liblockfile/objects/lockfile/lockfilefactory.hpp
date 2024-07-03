#pragma once

#include "ilockfilefactory.hpp"

namespace liblockfile {

class LockFileFactory : public ILockFileFactory {
public:
    virtual std::unique_ptr<ILockFileInternal> create() const override;
};

}