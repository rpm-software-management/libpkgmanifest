#pragma once

#include "ipackage.hpp"

#include "impl/common/yaml/iyamlnode.hpp"

#include <memory>

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

class IPackageSerializer {
public:
    virtual ~IPackageSerializer() = default;

    virtual std::unique_ptr<IYamlNode> serialize(const IPackage & package) const = 0;
};

}