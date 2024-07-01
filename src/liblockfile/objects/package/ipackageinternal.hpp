#pragma once

#include "ipackagesetter.hpp"

#include "liblockfile/ipackage.hpp"

namespace liblockfile {

class IPackageInternal : public IPackage, public IPackageSetter {
};

}