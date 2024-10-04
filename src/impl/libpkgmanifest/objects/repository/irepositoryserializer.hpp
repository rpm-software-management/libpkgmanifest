#pragma once

#include "irepository.hpp"

#include "libpkgmanifest/yaml/iyamlnode.hpp"

#include <memory>

namespace libpkgmanifest::internal {

class IRepositorySerializer {
public:
    virtual ~IRepositorySerializer() = default;

    virtual std::unique_ptr<IYamlNode> serialize(const IRepository & repository) const = 0;
};

}