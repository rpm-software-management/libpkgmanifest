#pragma once

#include "manifest.hpp"

#include <memory>
#include <string>

namespace libpkgmanifest {

class Validator {
public:
    Validator();
    ~Validator();

    void validate(const std::string & path) const;

private:
    class Impl;
    std::unique_ptr<Impl> p_impl;
};

}