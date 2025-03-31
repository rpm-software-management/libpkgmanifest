#pragma once

#include "libpkgmanifest/common/version.hpp"

#include "api/shared/base_impl.hpp"
#include "impl/common/objects/version/versionfactory.hpp"

namespace libpkgmanifest::common {

using namespace libpkgmanifest::internal::common;

class Version::Impl : public BaseImpl<IVersion, VersionFactory> {
    using BaseImpl<IVersion, VersionFactory>::BaseImpl;
};

}