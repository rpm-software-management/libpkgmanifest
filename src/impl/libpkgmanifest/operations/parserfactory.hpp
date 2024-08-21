#pragma once

#include "iparserfactory.hpp"

namespace libpkgmanifest::internal {

class ParserFactory : public IParserFactory {
public:
    virtual std::unique_ptr<IParser> create() const override;
};

}