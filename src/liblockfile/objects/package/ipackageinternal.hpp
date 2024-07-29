#pragma once

#include "ipackage.hpp"
#include "ipackagesetter.hpp"

namespace liblockfile {

class IPackageInternal : public IPackage, public IPackageSetter {
};

}