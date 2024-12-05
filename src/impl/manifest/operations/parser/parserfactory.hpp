#pragma once

#include "iparserfactory.hpp"

namespace libpkgmanifest::internal::manifest {

class ParserFactory : public IParserFactory {
public:
    virtual std::unique_ptr<IParser> create() const override;
};

}