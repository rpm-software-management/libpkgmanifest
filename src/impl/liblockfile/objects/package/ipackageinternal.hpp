#pragma once

#include "ipackage.hpp"
#include "ipackagesetter.hpp"

namespace liblockfile::internal {

class IPackageInternal : public IPackage, public IPackageSetter {
};

}