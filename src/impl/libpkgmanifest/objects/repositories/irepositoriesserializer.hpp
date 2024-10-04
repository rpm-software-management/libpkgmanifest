#pragma once

#include "irepositories.hpp"

#include "libpkgmanifest/yaml/iyamlnode.hpp"

#include <memory>

namespace libpkgmanifest::internal {

class IRepositoriesSerializer {
public:
    virtual ~IRepositoriesSerializer() = default;

    virtual std::unique_ptr<IYamlNode> serialize(const IRepositories & packages) const = 0;
};

}