#include "manifest.hpp"

namespace libpkgmanifest::internal {

Manifest::Manifest()
    : document()
    , version(nullptr)
    , packages(nullptr) {}

Manifest::Manifest(const Manifest & other) 
    : document(other.document)
    , version(other.version->clone())
    , packages(other.packages->clone()) {}

std::unique_ptr<IManifest> Manifest::clone() const {
    return std::unique_ptr<IManifest>(new Manifest(*this));
}

std::string Manifest::get_document() const {
    return document;
}

const IVersion & Manifest::get_version() const {
    return *version;
}

IVersion & Manifest::get_version() {
    return *version;
}

const IPackages & Manifest::get_packages() const {
    return *packages;
}

IPackages & Manifest::get_packages() {
    return *packages;
}

void Manifest::set_document(const std::string & document) {
    this->document = document;
}

void Manifest::set_version(std::unique_ptr<IVersion> version) {
    this->version = std::move(version);
}

void Manifest::set_packages(std::unique_ptr<IPackages> packages) {
    this->packages = std::move(packages);
}

}
