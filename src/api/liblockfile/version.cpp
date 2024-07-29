#include "liblockfile/version.hpp"

#include "version_impl.hpp"

namespace liblockfile {

Version::Version() : p_impl(std::make_unique<Impl>()) {}

Version::~Version() = default;

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