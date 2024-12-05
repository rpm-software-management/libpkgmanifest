#pragma once

#include "iserializer.hpp"

#include <memory>

namespace libpkgmanifest::internal::manifest {

class ISerializerFactory {
public:
    virtual ~ISerializerFactory() = default;

    virtual std::unique_ptr<ISerializer> create() const = 0;
};

}