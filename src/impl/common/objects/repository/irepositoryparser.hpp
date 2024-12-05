#pragma once

#include "irepository.hpp"

#include "impl/common/yaml/iyamlnode.hpp"

#include <memory>

namespace libpkgmanifest::internal::common {

class IRepositoryParser {
public:
    virtual ~IRepositoryParser() = default;

    virtual std::unique_ptr<IRepository> parse(const IYamlNode & node) const = 0;
};

}