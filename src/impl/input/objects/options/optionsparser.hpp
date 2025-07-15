// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "ioptionsfactory.hpp"
#include "ioptionsparser.hpp"

namespace libpkgmanifest::internal::input {

class OptionsParser : public IOptionsParser {
public:
    OptionsParser(std::shared_ptr<IOptionsFactory> options_factory);

    virtual std::unique_ptr<IOptions> parse(const IYamlNode & node) const override;

private:
    std::shared_ptr<IOptionsFactory> options_factory;
};

}