#pragma once

#include "liblockfile/ipackage.hpp"

#include <memory>

namespace liblockfile {

class IPackagesSetter {
public:
    virtual ~IPackagesSetter() = default;

    virtual void add_package(std::unique_ptr<IPackage> package) = 0;
};

}