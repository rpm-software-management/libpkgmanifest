#pragma once

#include "iserializer.hpp"

#include <memory>

namespace liblockfile::internal {

class ISerializerFactory {
public:
    virtual ~ISerializerFactory() = default;

    virtual std::unique_ptr<ISerializer> create() const = 0;
};

}