#pragma once

#include "liblockfile/package.hpp"
#include "liblockfile/checksum.hpp"

#include "liblockfile/objects/package/ipackage.hpp"

#include "checksum_impl.hpp"

namespace liblockfile {

class Package::Impl {
public:
    void set(const internal::IPackage & package) {
        this->package = &package;
        checksum.p_impl->set(package.get_checksum());
    }
private:
    friend Package;
    const internal::IPackage * package;
    Checksum checksum;
};

}