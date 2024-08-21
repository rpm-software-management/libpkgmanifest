#pragma once

#include "packages.hpp"
#include "version.hpp"

#include <memory>
#include <string>

namespace libpkgmanifest {

class Manifest {
public:
    Manifest();
    ~Manifest();

    Manifest(const Manifest & other);
    Manifest & operator=(const Manifest & other);

    Manifest(Manifest && other) noexcept;
    Manifest & operator=(Manifest && other) noexcept;

    std::string get_document() const;
    Version & get_version();
    Packages & get_packages();

    void set_document(const std::string & document);
    void set_version(Version & version);
    void set_packages(Packages & packages);

private:
    friend class Parser;
    friend class Serializer;

    class Impl;
    std::unique_ptr<Impl> p_impl;
};

}