#pragma once

#include "ilockfile.hpp"

#include "liblockfile/yaml/iyamlnode.hpp"

#include <memory>

namespace liblockfile {

class ILockFileSerializer {
public:
    virtual ~ILockFileSerializer() = default;

    virtual std::unique_ptr<IYamlNode> serialize(const ILockFile & file) const = 0;
};

}