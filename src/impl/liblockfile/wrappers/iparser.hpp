#pragma once

#include "liblockfile/objects/lockfile/ilockfile.hpp"

#include <memory>
#include <string>

namespace liblockfile::internal {

class IParser {
public:
    virtual ~IParser() = default;

    virtual std::unique_ptr<ILockFile> parse(const std::string & path) const = 0;
};

}