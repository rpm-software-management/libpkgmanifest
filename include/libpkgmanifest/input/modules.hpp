// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <memory>
#include <string>
#include <vector>

namespace libpkgmanifest::input {

/// @brief A container with modular packages and their associated actions.
class Modules {
public:
    Modules();
    ~Modules();

    Modules(const Modules & other);
    Modules & operator=(const Modules & other);

    Modules(Modules && other) noexcept;
    Modules & operator=(Modules && other) noexcept;

    /// @brief Retrieves a list of modules to be enabled for resolving manifest content.
    ///
    /// @return A vector containing modules to be enabled.
    std::vector<std::string> & get_enables();

    /// @brief Retrieves a list of modules to be disabled for resolving manifest content.
    ///
    /// @return A vector containing modules to be disabled.
    std::vector<std::string> & get_disables();

private:
    friend class Input;

    class Impl;
    std::unique_ptr<Impl> p_impl;
};

}