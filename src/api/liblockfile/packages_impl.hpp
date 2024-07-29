#pragma once

#include "liblockfile/packages.hpp"
#include "liblockfile/package.hpp"

#include "liblockfile/objects/packages/ipackages.hpp"

#include "package_impl.hpp"

namespace liblockfile {

class Packages::Impl {
public:
    void set(const internal::IPackages & packages) {
        for (const auto & [arch, internal_arch_packages] : packages.get()) {
            std::vector<Package> arch_packages;
            arch_packages.reserve(internal_arch_packages.size());
            for (const auto & internal_package : internal_arch_packages) {
                Package package;
                package.p_impl->set(*internal_package);
                arch_packages.push_back(std::move(package));
            }
            packages_map.insert({arch, std::move(arch_packages)});
        }
    }
private:
    friend Packages;
    std::map<std::string, std::vector<Package>> packages_map;
};

}