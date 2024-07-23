#pragma once

#include "iyamlnodeinternal.hpp"

#include <memory>

namespace liblockfile {

class IYamlNodeFactory {
public:
    virtual ~IYamlNodeFactory() = default;

    virtual std::unique_ptr<IYamlNodeInternal> create() const = 0;
};

}