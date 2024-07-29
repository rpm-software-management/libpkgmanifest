#include "lockfile.hpp"

namespace liblockfile::internal {

LockFile::LockFile()
    : document()
    , version(nullptr)
    , packages(nullptr) {}
    
std::string LockFile::get_document() const {
    return document;
}

const IVersion & LockFile::get_version() const {
    return *version;
}

const IPackages & LockFile::get_packages() const {
    return *packages;
}

void LockFile::set_document(const std::string & document) {
    this->document = document;
}

void LockFile::set_version(std::unique_ptr<IVersion> version) {
    this->version = std::move(version);
}

void LockFile::set_packages(std::unique_ptr<IPackages> packages) {
    this->packages = std::move(packages);
}

}
