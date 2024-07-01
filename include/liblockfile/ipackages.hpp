#pragma once

#include "ipackage.hpp"

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace liblockfile {

class IPackages {
public:
    virtual ~IPackages() = default;

    virtual const std::map<std::string, std::vector<std::unique_ptr<IPackage>>> & get() const = 0;
    virtual const std::vector<std::unique_ptr<IPackage>> & get(const std::string & arch) const = 0;
};

}