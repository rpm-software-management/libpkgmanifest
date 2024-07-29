#include "checksum.hpp"

namespace liblockfile::internal {

Checksum::Checksum()
    : method(ChecksumMethod::SHA256)
    , digest() {}

ChecksumMethod Checksum::get_method() const {
    return method;
}

std::string Checksum::get_digest() const {
    return digest;
}

void Checksum::set_method(ChecksumMethod method) {
    this->method = method;
}

void Checksum::set_digest(const std::string & digest) {
    this->digest = digest;
}

}