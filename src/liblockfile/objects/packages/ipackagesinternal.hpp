#pragma once

#include "ipackagessetter.hpp"

#include "liblockfile/ipackages.hpp"

namespace liblockfile {

class IPackagesInternal : public IPackages, public IPackagesSetter {
};

}