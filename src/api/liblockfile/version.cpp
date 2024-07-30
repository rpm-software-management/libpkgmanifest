#include "version_impl.hpp"

#include "liblockfile/version.hpp"

namespace liblockfile {

Version::Version() : p_impl(std::make_unique<Impl>()) {}

Version::~Version() = default;

Version::Version(const Version & other) : p_impl(new Impl(*other.p_impl)) {}

Version & Version::operator=(const Version & other) {
    if (this != &other) {
        if (p_impl) {
            *p_impl = *other.p_impl;
        } else {
            p_impl = std::make_unique<Impl>(*other.p_impl);
        }
    }

    return *this;
}

Version::Version(Version && other) noexcept = default;
Version & Version::operator=(Version && other) noexcept = default;

unsigned Version::get_major() const {
    return p_impl->version->get_major();
}

unsigned Version::get_minor() const {
    return p_impl->version->get_minor();
}

unsigned Version::get_patch() const {
    return p_impl->version->get_patch();
}

}