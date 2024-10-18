#include "serializer.hpp"

namespace libpkgmanifest::internal {

Serializer::Serializer(std::unique_ptr<IYamlSerializer> yaml_serializer, std::unique_ptr<IManifestSerializer> manifest_serializer)
    : yaml_serializer(std::move(yaml_serializer))
    , manifest_serializer(std::move(manifest_serializer)) {}

void Serializer::serialize_manifest(const IManifest & manifest, const std::string & path) const {
    auto node = manifest_serializer->serialize(manifest);
    yaml_serializer->to_file(*node, path);
}

}