#pragma once

#include "libpkgmanifest/manifest/module.hpp"

#include "api/shared/base_impl.hpp"
#include "impl/manifest/objects/module/modulefactory.hpp"

namespace libpkgmanifest::manifest {

using namespace libpkgmanifest::internal::manifest;

class Module::Impl : public BaseImpl<IModule, ModuleFactory> {};

}