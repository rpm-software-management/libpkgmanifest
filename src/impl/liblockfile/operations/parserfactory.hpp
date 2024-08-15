#pragma once

#include "iparserfactory.hpp"

namespace liblockfile::internal {

class ParserFactory : public IParserFactory {
public:
    virtual std::unique_ptr<IParser> create() const override;
};

}