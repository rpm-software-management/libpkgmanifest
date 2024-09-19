#include "nevra.hpp"

#include <format>

namespace libpkgmanifest::internal {

Nevra::Nevra()
    : name()
    , epoch()
    , version()
    , release()
    , arch() {}

std::unique_ptr<INevra> Nevra::clone() const {
    return std::unique_ptr<INevra>(new Nevra(*this));
}

std::string Nevra::get_name() const {
    return name;
}

std::string Nevra::get_epoch() const {
    return epoch;
}

std::string Nevra::get_version() const {
    return version;
}

std::string Nevra::get_release() const {
    return release;
}

std::string Nevra::get_arch() const {
    return arch;
}

void Nevra::set_name(const std::string & name) {
    this->name = name;
}

void Nevra::set_epoch(const std::string & epoch) {
    this->epoch = epoch;
}

void Nevra::set_version(const std::string & version) {
    this->version = version;
}

void Nevra::set_release(const std::string & release) {
    this->release = release;
}

void Nevra::set_arch(const std::string & arch) {
    this->arch = arch;
}

std::string Nevra::to_string() const {
    if (name.empty()) {
        return std::string();
    }

    return std::format("{}-{}.{}", name, to_evr_string(), arch);
}

std::string Nevra::to_evr_string() const {
    if (version.empty()) {
        return std::string();
    }

    std::string epoch_string;
    if (!epoch.empty() && epoch != "0") {
        epoch_string = epoch + ":";
    }

    return std::format("{}{}-{}", epoch_string, version, release);
}

}