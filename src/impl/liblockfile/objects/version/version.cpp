#include "version.hpp"

namespace liblockfile::internal {

Version::Version()
    : major(0)
    , minor(0)
    , patch(0) {}

std::unique_ptr<IVersion> Version::clone() const {
    return std::unique_ptr<IVersion>(new Version(*this));
}

unsigned Version::get_major() const {
    return major;
}

unsigned Version::get_minor() const {
    return minor;
}

unsigned Version::get_patch() const {
    return patch;
}

void Version::set_major(unsigned major) {
    this->major = major;
}

void Version::set_minor(unsigned minor) {
    this->minor = minor;
}

void Version::set_patch(unsigned patch) {
    this->patch = patch;
}

}