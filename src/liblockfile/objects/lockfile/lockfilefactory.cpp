#include "lockfilefactory.hpp"

namespace liblockfile {

std::unique_ptr<ILockFileInternal> LockFileFactory::create() const {
    throw; // TODO: return std::make_unique<LockFile>();
}   

}