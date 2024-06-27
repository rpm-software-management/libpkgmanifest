#pragma once

#include "liblockfile/ilockfile.hpp"
#include "liblockfile/yaml/iyamlnode.hpp"

#include <memory>

namespace liblockfile {

class ILockFileParser {
public:
    virtual ~ILockFileParser() = default;

    virtual std::unique_ptr<ILockFile> parse(IYamlNode & node) const = 0;
};

}