// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "istringlistparser.hpp"

namespace libpkgmanifest::internal::common {

class StringListParser : public IStringListParser {
public:
    StringListParser();

    virtual std::vector<std::string> parse(const IYamlNode & node) const override;
};

}