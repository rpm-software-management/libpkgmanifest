#include "checksumserializer.hpp"

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;
using ChecksumMethod = libpkgmanifest::manifest::ChecksumMethod;

ChecksumSerializer::ChecksumSerializer(
    std::shared_ptr<IYamlNodeFactory> node_factory)
    : node_factory(node_factory) {}

std::unique_ptr<IYamlNode> ChecksumSerializer::serialize(const IChecksum & checksum) const {
    std::string method_string;
    switch(checksum.get_method()) {
        case ChecksumMethod::CRC32:
            method_string = "crc32";
            break;
        case ChecksumMethod::CRC64:
            method_string = "crc64";
            break;
        case ChecksumMethod::MD5:
            method_string = "md5";
            break;
        case ChecksumMethod::SHA1:
            method_string = "sha1";
            break;
        case ChecksumMethod::SHA224:
            method_string = "sha224";
            break;
        case ChecksumMethod::SHA256:
            method_string = "sha256";
            break;
        case ChecksumMethod::SHA384:
            method_string = "sha384";
            break;
        case ChecksumMethod::SHA512:
            method_string = "sha512";
            break;
    }

    auto node = node_factory->create();
    node->set(method_string + ":" + checksum.get_digest());

    return node;
}

}