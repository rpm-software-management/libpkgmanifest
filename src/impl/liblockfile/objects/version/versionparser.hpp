#pragma once

#include "iversionfactory.hpp"
#include "iversionparser.hpp"

#include "liblockfile/tools/istringsplitter.hpp"

namespace liblockfile::internal {

class VersionParser : public IVersionParser {
public:
    VersionParser(std::unique_ptr<IVersionFactory> version_factory, std::shared_ptr<IStringSplitter> string_splitter);

    virtual std::unique_ptr<IVersionInternal> parse(const IYamlNode & node) const override;

private:
    std::unique_ptr<IVersionFactory> version_factory;
    std::shared_ptr<IStringSplitter> string_splitter;
};

}