// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <memory>
#include <string>
#include <vector>

namespace libpkgmanifest::internal::input {

class IModules {
public:
    virtual ~IModules() = default;

    virtual std::unique_ptr<IModules> clone() const = 0;

    virtual const std::vector<std::string> & get_enables() const = 0;
    virtual std::vector<std::string> & get_enables() = 0;
    virtual const std::vector<std::string> & get_disables() const = 0;
    virtual std::vector<std::string> & get_disables() = 0;
};

}