#include "lockfile.hpp"
#include "lockfilefactory.hpp"

namespace liblockfile {

std::unique_ptr<ILockFileInternal> LockFileFactory::create() const {
    return std::unique_ptr<ILockFileInternal>(new LockFile());
}   

}