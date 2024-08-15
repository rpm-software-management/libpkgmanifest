#pragma once

#include "ilockfile.hpp"

#include <memory>

namespace liblockfile::internal {

class ILockFileFactory {
public:
    virtual ~ILockFileFactory() = default;

    virtual std::unique_ptr<ILockFile> create() const = 0;
};

}