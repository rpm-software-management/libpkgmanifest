// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "iparserfactory.hpp"

namespace libpkgmanifest::internal::input {

class ParserFactory : public IParserFactory {
public:
    virtual std::unique_ptr<IParser> create() const override;
};

}