#pragma once

#include "irepositories.hpp"

#include "libpkgmanifest/yaml/iyamlnode.hpp"

#include <memory>

namespace libpkgmanifest::internal {

class IRepositoriesParser {
public:
    virtual ~IRepositoriesParser() = default;

    virtual std::unique_ptr<IRepositories> parse(const IYamlNode & node) const = 0;
};

}