#pragma once

#include "imodulefactory.hpp"

namespace libpkgmanifest::internal::manifest {

class ModuleFactory : public IModuleFactory {
public:
    virtual std::unique_ptr<IModule> create() const override;
};

}