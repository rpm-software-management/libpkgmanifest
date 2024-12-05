#pragma once

#include "iserializerfactory.hpp"

namespace libpkgmanifest::internal::manifest {

class SerializerFactory : public ISerializerFactory {
public:
    virtual std::unique_ptr<ISerializer> create() const override;
};

}