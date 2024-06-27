#include "checksumfactory.hpp"

namespace liblockfile {

std::unique_ptr<IChecksumInternal> ChecksumFactory::create() const {
    throw; // TODO: return std::make_unique<Checksum>();
}   

}