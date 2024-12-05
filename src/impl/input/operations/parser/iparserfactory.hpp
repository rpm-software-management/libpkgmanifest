#pragma once

#include "iparser.hpp"

#include <memory>

namespace libpkgmanifest::internal::input {

class IParserFactory {
public:
    virtual ~IParserFactory() = default;

    virtual std::unique_ptr<IParser> create() const = 0;
};

}