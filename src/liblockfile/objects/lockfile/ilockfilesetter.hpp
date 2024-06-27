#pragma once

#include "liblockfile/ipackages.hpp"
#include "liblockfile/iversion.hpp"

#include <memory>
#include <string>

namespace liblockfile {

class ILockFileSetter {
public:
    virtual ~ILockFileSetter() = default;

    virtual void set_document(const std::string & document) = 0;
    virtual void set_version(std::unique_ptr<IVersion> version) = 0;
    virtual void set_packages(std::unique_ptr<IPackages> packages) = 0;
};

}