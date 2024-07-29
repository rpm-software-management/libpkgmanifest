#pragma once

#include "ipackages.hpp"
#include "ipackagessetter.hpp"

namespace liblockfile {

class IPackagesInternal : public IPackages, public IPackagesSetter {
};

}