// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <memory>

namespace libpkgmanifest::input {

/// @brief A class containing options to override the default package manager behavior when resolving manifest content.
class Options {
public:
    Options();
    ~Options();

    Options(const Options & other);
    Options & operator=(const Options & other);

    Options(Options && other) noexcept;
    Options & operator=(Options && other) noexcept;

    /// @brief Checks if the package manager is allowed to remove installed packages to resolve dependency issues.
    ///
    /// @return True if the package manager is allowed to remove packages, otherwise false.
    bool get_allow_erasing() const;

    /// @brief Sets whether the package manager is allowed to remove installed packages to resolve dependency issues.
    ///
    /// @param value True to allow the package manager to remove packages, otherwise false.
    void set_allow_erasing(bool value);

private:
    friend class Input;

    class Impl;
    std::unique_ptr<Impl> p_impl;
};

}