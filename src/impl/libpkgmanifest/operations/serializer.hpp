#pragma once

#include "iserializer.hpp"

#include "impl/libpkgmanifest/objects/manifest/imanifestserializer.hpp"
#include "impl/libpkgmanifest/yaml/iyamlserializer.hpp"

namespace libpkgmanifest::internal {

class Serializer : public ISerializer {
public:
    Serializer(std::unique_ptr<IYamlSerializer> yaml_serializer, std::unique_ptr<IManifestSerializer> manifest_serializer);

    virtual void serialize_manifest(const IManifest & manifest, const std::string & path) const override;

private:
    std::unique_ptr<IYamlSerializer> yaml_serializer;
    std::unique_ptr<IManifestSerializer> manifest_serializer;
};

}