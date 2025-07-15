// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "inevra.hpp"

#include "impl/common/yaml/iyamlnode.hpp"

#include <memory>
#include <string>

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

class INevraParser {
public:
    virtual ~INevraParser() = default;

    virtual std::unique_ptr<INevra> parse(const IYamlNode & node) const = 0;
    virtual std::unique_ptr<INevra> parse(const std::string & name, const std::string & arch, const IYamlNode & node) const = 0;
};

}