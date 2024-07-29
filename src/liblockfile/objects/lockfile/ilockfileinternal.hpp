#pragma once

#include "ilockfile.hpp"
#include "ilockfilesetter.hpp"

namespace liblockfile {

class ILockFileInternal : public ILockFile, public ILockFileSetter {
};

}