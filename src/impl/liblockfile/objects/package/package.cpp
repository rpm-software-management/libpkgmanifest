#include "package.hpp"

namespace liblockfile::internal {

Package::Package()
    : arch()
    , repo_id()
    , url()
    , checksum(nullptr)
    , size(0)
    , nevra()
    , srpm() {}

Package::Package(const Package & other) 
    : arch(other.arch)
    , repo_id(other.repo_id)
    , url(other.url)
    , checksum(other.checksum->clone())
    , size(other.size)
    , nevra(other.nevra)
    , srpm(other.srpm) {}

std::unique_ptr<IPackage> Package::clone() const {
    return std::unique_ptr<IPackage>(new Package(*this));
}

std::string Package::get_arch() const {
    return arch;
}

std::string Package::get_repo_id() const {
    return repo_id;
}

std::string Package::get_url() const {
    return url;
}

const IChecksum & Package::get_checksum() const {
    return *checksum;
}

IChecksum & Package::get_checksum() {
    return *checksum;
}

uint64_t Package::get_size() const {
    return size;
}

std::string Package::get_nevra() const {
    return nevra;
}

std::string Package::get_srpm() const {
    return srpm;
}

void Package::set_arch(const std::string & arch) {
    this->arch = arch;
}

void Package::set_repo_id(const std::string & repo_id) {
    this->repo_id = repo_id;
}

void Package::set_url(const std::string & url) {
    this->url = url;
}

void Package::set_checksum(std::unique_ptr<IChecksum> checksum) {
    this->checksum = std::move(checksum);
}

void Package::set_size(uint64_t size) {
    this->size = size;
}

void Package::set_nevra(const std::string & nevra) {
    this->nevra = nevra;
}

void Package::set_srpm(const std::string & srpm) {
    this->srpm = srpm;
}

}