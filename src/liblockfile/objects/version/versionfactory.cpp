#include "versionfactory.hpp"

namespace liblockfile {

std::unique_ptr<IVersionInternal> VersionFactory::create() const {
    throw; // TODO: return std::make_unique<Version>();
}   

}