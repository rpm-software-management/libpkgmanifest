#include "checksum.hpp"
#include "checksumfactory.hpp"

namespace liblockfile {

std::unique_ptr<IChecksumInternal> ChecksumFactory::create() const {
    return std::unique_ptr<IChecksumInternal>(new Checksum());
}   

}