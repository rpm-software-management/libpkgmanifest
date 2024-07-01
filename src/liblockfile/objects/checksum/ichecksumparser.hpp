#pragma once

#include "ichecksuminternal.hpp"

#include "liblockfile/yaml/iyamlnode.hpp"

#include <memory>

namespace liblockfile {

class IChecksumParser {
public:
    virtual ~IChecksumParser() = default;

    virtual std::unique_ptr<IChecksumInternal> parse(const IYamlNode & node) const = 0;
};

}