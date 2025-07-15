// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "irepositoryfactory.hpp"
#include "irepositoryparser.hpp"

namespace libpkgmanifest::internal::common {

class RepositorySourceNotProvidedError : public std::runtime_error {
public:
    RepositorySourceNotProvidedError(const std::string & message);
};

class RepositoryParser : public IRepositoryParser {
public:
    RepositoryParser(std::shared_ptr<IRepositoryFactory> repository_factory);

    virtual std::unique_ptr<IRepository> parse(const IYamlNode & node) const override;

private:
    std::shared_ptr<IRepositoryFactory> repository_factory;
};

}