#pragma once

#include "iversion.hpp"

#include <memory>

namespace libpkgmanifest::internal {

class IVersionFactory {
public:
    virtual ~IVersionFactory() = default;

    virtual std::unique_ptr<IVersion> create() const = 0;
};

}