#pragma once

#include "imodule.hpp"

#include <memory>

namespace libpkgmanifest::internal {

class IModuleFactory {
public:
    virtual ~IModuleFactory() = default;

    virtual std::unique_ptr<IModule> create() const = 0;
};

}