#pragma once

#include "ichecksumfactory.hpp"
#include "ichecksumparser.hpp"

#include "liblockfile/tools/istringsplitter.hpp"

namespace liblockfile::internal {

class ChecksumParser : public IChecksumParser {
public:
    ChecksumParser(std::unique_ptr<IChecksumFactory> checksum_factory, std::shared_ptr<IStringSplitter> string_splitter);

    virtual std::unique_ptr<IChecksumInternal> parse(const IYamlNode & node) const override;

private:
    std::unique_ptr<IChecksumFactory> checksum_factory;
    std::shared_ptr<IStringSplitter> string_splitter;
};

}