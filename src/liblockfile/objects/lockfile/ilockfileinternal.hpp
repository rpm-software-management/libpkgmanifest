#pragma once

#include "ilockfilesetter.hpp"

#include "liblockfile/ilockfile.hpp"

namespace liblockfile {

class ILockFileInternal : public ILockFile, public ILockFileSetter {
};

}