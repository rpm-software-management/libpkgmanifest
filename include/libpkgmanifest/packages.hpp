#pragma once

#include "package.hpp"

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace libpkgmanifest {

class Packages {
public:
    Packages();
    ~Packages();

    Packages(const Packages & other);
    Packages & operator=(const Packages & other);

    Packages(Packages && other) noexcept;
    Packages & operator=(Packages && other) noexcept;

    std::map<std::string, std::vector<Package>> get() const;
    std::vector<Package> get(const std::string & arch) const;

    void add(Package & package);

private:
    friend class Manifest;

    class Impl;
    std::unique_ptr<Impl> p_impl;
};

}