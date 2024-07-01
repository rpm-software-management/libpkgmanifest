#include "version.hpp"
#include "versionfactory.hpp"

namespace liblockfile {

std::unique_ptr<IVersionInternal> VersionFactory::create() const {
    return std::unique_ptr<IVersionInternal>(new Version());
}   

}