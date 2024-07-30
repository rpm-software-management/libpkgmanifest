#pragma once

#include "package.hpp"

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace liblockfile {

class Packages {
public:
    ~Packages();

    Packages(const Packages & other);
    Packages & operator=(const Packages & other);

    Packages(Packages && other) noexcept;
    Packages & operator=(Packages && other) noexcept;

    const std::map<std::string, std::vector<Package>> & get() const;
    const std::vector<Package> & get(const std::string & arch) const;

private:
    friend class LockFile;

    Packages();

    class Impl;
    std::unique_ptr<Impl> p_impl;
};

}