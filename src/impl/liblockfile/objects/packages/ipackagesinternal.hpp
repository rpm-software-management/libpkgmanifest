#pragma once

#include "ipackages.hpp"
#include "ipackagessetter.hpp"

namespace liblockfile::internal {

class IPackagesInternal : public IPackages, public IPackagesSetter {
};

}