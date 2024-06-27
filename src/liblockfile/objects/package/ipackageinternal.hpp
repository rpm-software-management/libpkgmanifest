#pragma once

#include "ipackagesetter.hpp"

#include "liblockfile/ipackage.hpp"

namespace liblockfile {

class IPackageInternal : IPackage, IPackageSetter {
};

}