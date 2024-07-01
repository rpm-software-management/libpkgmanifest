#include "checksumparser.hpp"

#include <algorithm>
#include <cctype>

namespace liblockfile {

ChecksumParser::ChecksumParser(
    const IChecksumFactory & checksum_factory)
    : checksum_factory(checksum_factory) {}

std::unique_ptr<IChecksumInternal> ChecksumParser::parse(const IYamlNode & node) const {
    auto checksum = checksum_factory.create();
    auto checksum_string = node.as_string();

    std::string method_string;
    std::string digest;

    // TODO: Handle not found case?
    auto pos = checksum_string.find(':');
    method_string = checksum_string.substr(0, pos);
    digest = checksum_string.substr(pos + 1);

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