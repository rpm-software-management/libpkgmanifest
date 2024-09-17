#include "module.hpp"
#include "modulefactory.hpp"

namespace libpkgmanifest::internal {

std::unique_ptr<IModule> ModuleFactory::create() const {
    return std::unique_ptr<IModule>(new Module());
}   

}