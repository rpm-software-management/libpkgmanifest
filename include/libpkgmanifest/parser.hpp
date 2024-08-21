#pragma once

#include "manifest.hpp"

#include <memory>
#include <string>

namespace libpkgmanifest {

class Parser {
public:
    Parser();
    ~Parser();

    Manifest parse(const std::string & path) const;

private:
    class Impl;
    std::unique_ptr<Impl> p_impl;
};

}