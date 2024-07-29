#pragma once

#include "liblockfile/objects/package/ipackage.hpp"

#include <memory>

namespace liblockfile::internal {

class IPackagesSetter {
public:
    virtual ~IPackagesSetter() = default;

    virtual void add(std::unique_ptr<IPackage> package) = 0;
};

}