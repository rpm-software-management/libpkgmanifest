#include "package.hpp"

namespace libpkgmanifest::internal {

Package::Package()
    : repo_id()
    , url()
    , size(0)
    , checksum(nullptr)
    , nevra(nullptr)
    , srpm(nullptr)
    , module(nullptr) {}

Package::Package(const Package & other) 
    : repo_id(other.repo_id)
    , url(other.url)
    , size(other.size)
    , checksum(other.checksum->clone())
    , nevra(other.nevra->clone())
    , srpm(other.srpm->clone())
    , module(other.module->clone()) {}

std::unique_ptr<IPackage> Package::clone() const {
    return std::unique_ptr<IPackage>(new Package(*this));
}

std::string Package::get_repo_id() const {
    return repo_id;
}

std::string Package::get_url() const {
    return url;
}

uint64_t Package::get_size() const {
    return size;
}

const IChecksum & Package::get_checksum() const {
    return *checksum;
}

IChecksum & Package::get_checksum() {
    return *checksum;
}

const INevra & Package::get_nevra() const {
    return *nevra;
}

INevra & Package::get_nevra() {
    return *nevra;
}

const INevra & Package::get_srpm() const {
    return *srpm;
}

INevra & Package::get_srpm() {
    return *srpm;
}

const IModule & Package::get_module() const {
    return *module;
}

IModule & Package::get_module() {
    return *module;
}

void Package::set_repo_id(const std::string & repo_id) {
    this->repo_id = repo_id;
}

void Package::set_url(const std::string & url) {
    this->url = url;
}

void Package::set_size(uint64_t size) {
    this->size = size;
}

void Package::set_checksum(std::unique_ptr<IChecksum> checksum) {
    this->checksum = std::move(checksum);
}

void Package::set_nevra(std::unique_ptr<INevra> nevra) {
    this->nevra = std::move(nevra);
}

void Package::set_srpm(std::unique_ptr<INevra> srpm) {
    this->srpm = std::move(srpm);
}

void Package::set_module(std::unique_ptr<IModule> module) {
    this->module = std::move(module);
}

}