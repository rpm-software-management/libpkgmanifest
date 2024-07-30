#include "checksum_impl.hpp"

#include "liblockfile/checksum.hpp"

namespace liblockfile {

Checksum::Checksum() : p_impl(std::make_unique<Impl>()) {}

Checksum::~Checksum() = default;

Checksum::Checksum(const Checksum & other) : p_impl(new Impl(*other.p_impl)) {}

Checksum & Checksum::operator=(const Checksum & other) {
    if (this != &other) {
        if (p_impl) {
            *p_impl = *other.p_impl;
        } else {
            p_impl = std::make_unique<Impl>(*other.p_impl);
        }
    }

    return *this;
}

Checksum::Checksum(Checksum && other) noexcept = default;
Checksum & Checksum::operator=(Checksum && other) noexcept = default;

ChecksumMethod Checksum::get_method() const {
    return p_impl->checksum->get_method();
}
    
std::string Checksum::get_digest() const {
    return p_impl->checksum->get_digest();
}

}