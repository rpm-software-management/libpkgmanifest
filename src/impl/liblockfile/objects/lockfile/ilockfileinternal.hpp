#pragma once

#include "ilockfile.hpp"
#include "ilockfilesetter.hpp"

namespace liblockfile::internal {

class ILockFileInternal : public ILockFile, public ILockFileSetter {
};

}