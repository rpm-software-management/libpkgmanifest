#pragma once

#include "package.hpp"

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace liblockfile {

class Packages {
public:
    const std::map<std::string, std::vector<Package>> & get() const;
    const std::vector<Package> & get(const std::string & arch) const;

private:
    friend class LockFile;

    Packages();
    ~Packages();

    class Impl;
    std::unique_ptr<Impl> p_impl;
};

}