// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "iversionserializer.hpp"

#include "impl/common/yaml/iyamlnodefactory.hpp"

namespace libpkgmanifest::internal::common {

class VersionSerializer : public IVersionSerializer {
public:
    VersionSerializer(std::shared_ptr<IYamlNodeFactory> node_factory);

    virtual std::unique_ptr<IYamlNode> serialize(const IVersion & version) const override;

private:
    std::shared_ptr<IYamlNodeFactory> node_factory;
};

}