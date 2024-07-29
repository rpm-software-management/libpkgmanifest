#include "liblockfile/checksum.hpp"

#include "checksum_impl.hpp"

namespace liblockfile {

Checksum::Checksum() : p_impl(std::make_unique<Impl>()) {}

Checksum::~Checksum() = default;

ChecksumMethod Checksum::get_method() const {
    return p_impl->checksum->get_method();
}
    
std::string Checksum::get_digest() const {
    return p_impl->checksum->get_digest();
}

}