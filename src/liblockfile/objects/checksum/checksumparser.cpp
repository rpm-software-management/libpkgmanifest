#include "checksumparser.hpp"

#include <algorithm>
#include <cctype>

namespace liblockfile {

ChecksumParser::ChecksumParser(
    std::unique_ptr<IChecksumFactory> checksum_factory,
    std::shared_ptr<IStringSplitter> string_splitter)
    : checksum_factory(std::move(checksum_factory))
    , string_splitter(string_splitter) {}

std::unique_ptr<IChecksumInternal> ChecksumParser::parse(const IYamlNode & node) const {
    auto checksum = checksum_factory->create();
    auto checksum_string = node.as_string();

    // TODO: Handle not found case?
    auto checksum_parts = string_splitter->split(checksum_string, ':');
    auto & method_string = checksum_parts[0];
    auto & digest = checksum_parts[1];

    // case-insensitive method matching
    std::transform(method_string.begin(), method_string.end(), method_string.begin(),
        [](unsigned char c){ return std::tolower(c); });

    // TODO: Handle unknown method case?
    if (method_string == "sha256") {
        checksum->set_method(ChecksumMethod::SHA256);
    } else if (method_string == "sha512") {
        checksum->set_method(ChecksumMethod::SHA512);
    } else if (method_string == "md5") {
        checksum->set_method(ChecksumMethod::MD5);
    } else if (method_string == "crc32") {
        checksum->set_method(ChecksumMethod::CRC32);
    } else if (method_string == "crc64") {
        checksum->set_method(ChecksumMethod::CRC64);
    }

    checksum->set_digest(digest);
    
    return checksum;
}

}