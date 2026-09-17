// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "impl/common/yaml/iyamlnodefactory.hpp"
#include "iprototypefileconverter.hpp"

namespace libpkgmanifest::internal::input {

using namespace libpkgmanifest::internal::common;

class PrototypeFileConverter : public IPrototypeFileConverter {
public:
    PrototypeFileConverter(std::shared_ptr<IYamlNodeFactory> node_factory);

    virtual std::unique_ptr<IYamlNode> convert(const IYamlNode & node) const override;

private:
    std::shared_ptr<IYamlNodeFactory> node_factory;
};

}  // namespace libpkgmanifest::internal::input
