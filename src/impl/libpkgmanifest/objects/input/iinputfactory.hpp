#pragma once

#include "iinput.hpp"

#include <memory>

namespace libpkgmanifest::internal {

class IInputFactory {
public:
    virtual ~IInputFactory() = default;

    virtual std::unique_ptr<IInput> create() const = 0;
};

}