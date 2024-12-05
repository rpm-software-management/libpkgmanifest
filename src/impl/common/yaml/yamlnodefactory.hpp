#pragma once

#include "iyamlnodefactory.hpp"

namespace libpkgmanifest::internal::common {

class YamlNodeFactory : public IYamlNodeFactory {
public:
    virtual std::unique_ptr<IYamlNodeInternal> create() const override;
};

}