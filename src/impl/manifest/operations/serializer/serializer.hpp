// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "impl/common/yaml/iyamlserializer.hpp"
#include "impl/manifest/objects/manifest/imanifestserializer.hpp"
#include "iserializer.hpp"

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

class Serializer : public ISerializer {
public:
    Serializer(
        std::unique_ptr<IYamlSerializer> yaml_serializer, std::unique_ptr<IManifestSerializer> manifest_serializer);

    virtual void serialize_manifest(const IManifest & manifest, const std::string & path) const override;

private:
    std::unique_ptr<IYamlSerializer> yaml_serializer;
    std::unique_ptr<IManifestSerializer> manifest_serializer;
};

}  // namespace libpkgmanifest::internal::manifest
