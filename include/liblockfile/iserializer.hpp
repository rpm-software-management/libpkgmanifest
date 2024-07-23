#pragma once

#include "ilockfile.hpp"

#include <string>

namespace liblockfile {

class ISerializer {
public:
    virtual ~ISerializer() = default;

    virtual void serialize(const ILockFile & file, const std::string & path) const = 0;
};

}