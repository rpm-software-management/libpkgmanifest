#pragma once

#include "ipackage.hpp"

#include <memory>
#include <string>
#include <vector>

namespace liblockfile {

class IPackages {
public:
    virtual ~IPackages() = default;

    virtual const std::vector<std::unique_ptr<IPackage>> & get_by_arch(const std::string & arch) const = 0;
    virtual const std::vector<std::unique_ptr<IPackage>> & get() const = 0;
};

}