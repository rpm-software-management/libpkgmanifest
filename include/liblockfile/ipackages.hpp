#pragma once

#include "ipackage.hpp"

#include <string>
#include <vector>

namespace liblockfile {

class IPackages {
public:
    virtual ~IPackages() = default;

    virtual const std::vector<IPackage> & get_by_arch(const std::string & arch) const = 0;
    virtual const std::vector<IPackage> & get() const = 0;
};

}