#include "modules.hpp"
#include "modulesfactory.hpp"

namespace libpkgmanifest::internal::input {

std::unique_ptr<IModules> ModulesFactory::create() const {
    return std::unique_ptr<IModules>(new Modules());
}   

}