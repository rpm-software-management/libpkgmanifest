#pragma once

#include "imodulesfactory.hpp"

namespace libpkgmanifest::internal::input {

class ModulesFactory : public IModulesFactory {
public:
    virtual std::unique_ptr<IModules> create() const override;
};

}