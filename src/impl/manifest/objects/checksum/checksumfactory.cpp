#include "checksum.hpp"
#include "checksumfactory.hpp"

namespace libpkgmanifest::internal::manifest {

std::unique_ptr<IChecksum> ChecksumFactory::create() const {
    return std::unique_ptr<IChecksum>(new Checksum());
}   

}