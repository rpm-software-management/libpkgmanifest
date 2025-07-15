// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "iprototypefileconverter.hpp"

#include "impl/common/yaml/iyamlnodefactory.hpp"

namespace libpkgmanifest::internal::input {

using namespace libpkgmanifest::internal::common;

constexpr const char * INPUT_PROTOTYPE_DOCUMENT_ID = "rpm-package-input-prototype";

constexpr int INPUT_PROTOTYPE_DOCUMENT_VERSION_MAJOR = 0;
constexpr int INPUT_PROTOTYPE_DOCUMENT_VERSION_MINOR = 0;
constexpr int INPUT_PROTOTYPE_DOCUMENT_VERSION_PATCH = 1;

class PrototypeFileConverter : public IPrototypeFileConverter {
public:
    PrototypeFileConverter(std::shared_ptr<IYamlNodeFactory> node_factory);

    virtual std::unique_ptr<IYamlNode> convert(const IYamlNode & node) const override;

private:
    std::shared_ptr<IYamlNodeFactory> node_factory;
};

}