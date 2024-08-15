#pragma once

#include "iserializerfactory.hpp"

namespace liblockfile::internal {

class SerializerFactory : public ISerializerFactory {
public:
    virtual std::unique_ptr<ISerializer> create() const override;
};

}