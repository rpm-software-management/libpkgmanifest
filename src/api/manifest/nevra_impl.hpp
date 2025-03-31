#pragma once

#include "libpkgmanifest/manifest/nevra.hpp"

#include "api/shared/base_impl.hpp"
#include "impl/manifest/objects/nevra/nevrafactory.hpp"

namespace libpkgmanifest::manifest {

using namespace libpkgmanifest::internal::manifest;

class Nevra::Impl : public BaseImpl<INevra, NevraFactory> {
    using BaseImpl<INevra, NevraFactory>::BaseImpl;
};

}