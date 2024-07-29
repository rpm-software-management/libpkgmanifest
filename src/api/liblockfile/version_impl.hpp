#pragma once

#include "liblockfile/version.hpp"

#include "liblockfile/objects/version/iversion.hpp"

namespace liblockfile {

class Version::Impl {
public:
    void set(const internal::IVersion & version) {
        this->version = &version;
    }
private:
    friend Version;
    const internal::IVersion * version;
};

}