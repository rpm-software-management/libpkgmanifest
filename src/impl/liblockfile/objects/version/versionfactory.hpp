#pragma once

#include "iversionfactory.hpp"

namespace liblockfile::internal {

class VersionFactory : public IVersionFactory {
public:
    virtual std::unique_ptr<IVersionInternal> create() const override;
};

}