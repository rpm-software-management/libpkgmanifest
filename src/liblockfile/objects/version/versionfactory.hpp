#pragma once

#include "iversionfactory.hpp"

namespace liblockfile {

class VersionFactory : IVersionFactory {
public:
    virtual std::unique_ptr<IVersionInternal> create() const override;
};

}