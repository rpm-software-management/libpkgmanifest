#pragma once

#include "ioptionsfactory.hpp"

namespace libpkgmanifest::internal::input {

class OptionsFactory : public IOptionsFactory {
public:
    virtual std::unique_ptr<IOptions> create() const override;
};

}