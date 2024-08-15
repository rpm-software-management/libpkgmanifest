#pragma once

#include "liblockfile/objects/lockfile/ilockfile.hpp"

#include <string>

namespace liblockfile::internal {

class ISerializer {
public:
    virtual ~ISerializer() = default;

    virtual void serialize(const ILockFile & file, const std::string & path) const = 0;
};

}