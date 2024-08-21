#pragma once

#include "manifest.hpp"

#include <memory>
#include <string>

namespace libpkgmanifest {

class Serializer {
public:
    Serializer();
    ~Serializer();

    void serialize(const Manifest & manifest, const std::string & path) const;

private:
    class Impl;
    std::unique_ptr<Impl> p_impl;
};

}