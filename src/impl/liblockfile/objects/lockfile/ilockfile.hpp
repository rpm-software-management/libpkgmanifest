#pragma once

#include "liblockfile/objects/packages/ipackages.hpp"
#include "liblockfile/objects/version/iversion.hpp"

#include <string>

namespace liblockfile::internal {

class ILockFile {
public:
    virtual ~ILockFile() = default;

    virtual std::string get_document() const = 0;
    virtual const IVersion & get_version() const = 0;
    virtual const IPackages & get_packages() const = 0;
};

}