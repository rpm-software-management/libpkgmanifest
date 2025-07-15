// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "ipackagesfactory.hpp"
#include "ipackagesparser.hpp"

#include "impl/common/operations/stringlistparser/istringlistparser.hpp"

namespace libpkgmanifest::internal::input {

using namespace libpkgmanifest::internal::common;

class PackagesParser : public IPackagesParser {
public:
    PackagesParser(
        std::shared_ptr<IPackagesFactory> packages_factory,
        std::shared_ptr<IStringListParser> string_list_parser);

    virtual std::unique_ptr<IPackages> parse(const IYamlNode & node) const override;

private:
    std::shared_ptr<IPackagesFactory> packages_factory;
    std::shared_ptr<IStringListParser> string_list_parser;
};

}