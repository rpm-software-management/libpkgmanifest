#pragma once

#include "lockfile.hpp"

#include <memory>
#include <string>

namespace liblockfile {

class Serializer {
public:
    Serializer();
    ~Serializer();

    void serialize(const LockFile & file, const std::string & path) const;

private:
    class Impl;
    std::unique_ptr<Impl> p_impl;
};

}