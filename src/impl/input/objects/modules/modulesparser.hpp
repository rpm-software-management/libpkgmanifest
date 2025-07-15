// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "imodulesfactory.hpp"
#include "imodulesparser.hpp"

#include "impl/common/operations/stringlistparser/istringlistparser.hpp"

namespace libpkgmanifest::internal::input {

using namespace libpkgmanifest::internal::common;

class ModulesParser : public IModulesParser {
public:
    ModulesParser(
        std::shared_ptr<IModulesFactory> modules_factory,
        std::shared_ptr<IStringListParser> string_list_parser);

    virtual std::unique_ptr<IModules> parse(const IYamlNode & node) const override;

private:
    std::shared_ptr<IModulesFactory> modules_factory;
    std::shared_ptr<IStringListParser> string_list_parser;
};

}