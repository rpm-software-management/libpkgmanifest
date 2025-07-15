// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "checksumparser.hpp"

#include <algorithm>
#include <cctype>

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;
using ChecksumMethod = libpkgmanifest::manifest::ChecksumMethod;

ChecksumFormatError::ChecksumFormatError(const std::string & message) : std::runtime_error(message) {}

ChecksumParser::ChecksumParser(
    std::shared_ptr<IChecksumFactory> checksum_factory,
    std::shared_ptr<IStringSplitter> string_splitter)
    : checksum_factory(std::move(checksum_factory))
    , string_splitter(std::move(string_splitter)) {}

std::unique_ptr<IChecksum> ChecksumParser::parse(const IYamlNode & node) const {
    auto checksum = checksum_factory->create();
    auto checksum_string = node.as_string();

    auto checksum_parts = string_splitter->split(checksum_string, ':');
    if (checksum_parts.size() != 2) {
        throw ChecksumFormatError("Checksum must be in format 'method:digest': " + checksum_string);
    }

    auto & method_string = checksum_parts[0];
    auto & digest = checksum_parts[1];

    // case-insensitive method matching
    std::transform(method_string.begin(), method_string.end(), method_string.begin(),
        [](unsigned char c){ return std::tolower(c); });

    if (method_string == "sha1") {
        checksum->set_method(ChecksumMethod::SHA1);
    } else if (method_string == "sha224") {
        checksum->set_method(ChecksumMethod::SHA224);
    } else if (method_string == "sha256") {
        checksum->set_method(ChecksumMethod::SHA256);
    } else if (method_string == "sha384") {
        checksum->set_method(ChecksumMethod::SHA384);
    } else if (method_string == "sha512") {
        checksum->set_method(ChecksumMethod::SHA512);
    } else if (method_string == "md5") {
        checksum->set_method(ChecksumMethod::MD5);
    } else if (method_string == "crc32") {
        checksum->set_method(ChecksumMethod::CRC32);
    } else if (method_string == "crc64") {
        checksum->set_method(ChecksumMethod::CRC64);
    } else {
        throw ChecksumFormatError("Unknown checksum method: " + method_string);
    }

    checksum->set_digest(digest);
    
    return checksum;
}

}