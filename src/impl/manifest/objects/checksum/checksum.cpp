#include "checksum.hpp"

namespace libpkgmanifest::internal::manifest {

using ChecksumMethod = libpkgmanifest::manifest::ChecksumMethod;

Checksum::Checksum()
    : method(ChecksumMethod::SHA256)
    , digest() {}

std::unique_ptr<IChecksum> Checksum::clone() const {
    return std::make_unique<Checksum>(*this);
}

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