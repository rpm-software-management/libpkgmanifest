// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "imodules.hpp"

namespace libpkgmanifest::internal::input {

class Modules : public IModules {
public:
    Modules();

    virtual std::unique_ptr<IModules> clone() const override;

    virtual const std::vector<std::string> & get_enables() const override;
    virtual std::vector<std::string> & get_enables() override;
    virtual const std::vector<std::string> & get_disables() const override;
    virtual std::vector<std::string> & get_disables() override;

private:
    std::vector<std::string> enables;
    std::vector<std::string> disables;
};

}