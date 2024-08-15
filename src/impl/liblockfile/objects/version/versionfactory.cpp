#include "version.hpp"
#include "versionfactory.hpp"

namespace liblockfile::internal {

std::unique_ptr<IVersion> VersionFactory::create() const {
    return std::unique_ptr<IVersion>(new Version());
}   

}