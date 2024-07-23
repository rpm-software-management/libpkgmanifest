#pragma once

#include "iyamlnodefactory.hpp"

namespace liblockfile {

class YamlNodeFactory : public IYamlNodeFactory {
public:
    virtual std::unique_ptr<IYamlNodeInternal> create() const override;
};

}