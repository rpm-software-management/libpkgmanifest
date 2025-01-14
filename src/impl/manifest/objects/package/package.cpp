#include "package.hpp"

#include <cstring>
#include <filesystem>
#include <format>

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

PackageRepositoryNotAttachedError::PackageRepositoryNotAttachedError(const std::string & message)
    : std::runtime_error(message) {}

Package::Package()
    : repo_id()
    , location()
    , size(0)
    , checksum(nullptr)
    , nevra(nullptr)
    , srpm(nullptr)
    , module(nullptr)
    , repository(nullptr) {}

Package::Package(const Package & other) 
    : repo_id(other.repo_id)
    , location(other.location)
    , size(other.size)
    , checksum(other.checksum->clone())
    , nevra(other.nevra->clone())
    , srpm(other.srpm->clone())
    , module(other.module->clone())
    , repository(other.repository) {}

std::unique_ptr<IPackage> Package::clone() const {
    return std::make_unique<Package>(*this);
}

std::string Package::get_repo_id() const {
    return repo_id;
}

std::string Package::get_location() const {
    return location;
}

std::string Package::get_url() const {
    if (!repository || repository->get_baseurl().empty()) {
        return std::string();
    }

    auto url = repository->get_baseurl();
    auto pos = url.find(ARCH_PLACEHOLDER);
    if (pos != std::string::npos) {
        url.replace(pos, strlen(ARCH_PLACEHOLDER), nevra->get_arch());
    }

    return std::filesystem::path(url) / location;
}

uint64_t Package::get_size() const {
    return size;
}

const IRepository & Package::get_repository() const {
    check_repository();
    return *repository;
}

IRepository & Package::get_repository() {
    check_repository();
    return *repository;
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

void Package::set_location(const std::string & location) {
    this->location = location;
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

void Package::set_repository(IRepository & repository) {
    this->repository = &repository;
}

void Package::check_repository() const {
    if (!repository) {
        throw PackageRepositoryNotAttachedError(std::format(
            "Repository is not configured yet for package '{}'", nevra->to_string()));
    }
}

}