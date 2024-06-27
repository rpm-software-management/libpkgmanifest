#include "version.hpp"

namespace liblockfile {

int Version::get_major() const {
    return major;
}

int Version::get_minor() const {
    return minor;
}

int Version::get_patch() const {
    return patch;
}

void Version::set_major(int major) {
    this->major = major;
}

void Version::set_minor(int minor) {
    this->minor = minor;
}

void Version::set_patch(int patch) {
    this->patch = patch;
}

}