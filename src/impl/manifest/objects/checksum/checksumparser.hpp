#pragma once

#include "ichecksumfactory.hpp"
#include "ichecksumparser.hpp"

#include "impl/common/tools/stringsplitter/istringsplitter.hpp"

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

class ChecksumParser : public IChecksumParser {
public:
    ChecksumParser(std::shared_ptr<IChecksumFactory> checksum_factory, std::shared_ptr<IStringSplitter> string_splitter);

    virtual std::unique_ptr<IChecksum> parse(const IYamlNode & node) const override;

private:
    std::shared_ptr<IChecksumFactory> checksum_factory;
    std::shared_ptr<IStringSplitter> string_splitter;
};

}