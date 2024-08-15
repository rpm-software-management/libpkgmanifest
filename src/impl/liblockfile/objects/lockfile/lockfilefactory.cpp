#include "lockfile.hpp"
#include "lockfilefactory.hpp"

namespace liblockfile::internal {

std::unique_ptr<ILockFile> LockFileFactory::create() const {
    return std::unique_ptr<ILockFile>(new LockFile());
}   

}