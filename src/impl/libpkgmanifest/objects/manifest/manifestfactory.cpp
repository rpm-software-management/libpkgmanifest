#include "manifest.hpp"
#include "manifestfactory.hpp"

namespace libpkgmanifest::internal {

std::unique_ptr<IManifest> ManifestFactory::create() const {
    return std::unique_ptr<IManifest>(new Manifest());
}   

}