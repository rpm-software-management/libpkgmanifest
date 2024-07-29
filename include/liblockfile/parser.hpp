#pragma once

#include "lockfile.hpp"

#include <memory>
#include <string>

namespace liblockfile {

class Parser {
public:
    Parser();
    ~Parser();

    LockFile parse(const std::string & path) const;

private:
    class Impl;
    std::unique_ptr<Impl> p_impl;
};

}