#pragma once

#include "ilockfilesetter.hpp"

#include "liblockfile/ilockfile.hpp"

namespace liblockfile {

class ILockFileInternal : ILockFile, ILockFileSetter {
};

}