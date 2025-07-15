// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <memory>
#include <string>

namespace libpkgmanifest::manifest {

/// @brief Format for the package identifier, including Name, (optional) Epoch, Version, Release, and Architecture fields.
///
/// @note For more details, refer to the official RPM documentation: https://rpm-software-management.github.io/rpm/manual/tags.html.
class Nevra {
public:
    Nevra();
    ~Nevra();

    Nevra(const Nevra & other);
    Nevra & operator=(const Nevra & other);

    Nevra(Nevra && other) noexcept;
    Nevra & operator=(Nevra && other) noexcept;

    /// @brief Retrieves the package name.
    ///
    /// @return The package name.
    std::string get_name() const;

    /// @brief Retrieves the package epoch.
    ///
    /// @note Can be empty if the epoch is not defined.
    ///
    /// @return The package epoch.
    std::string get_epoch() const;

    /// @brief Retrieves the package version.
    ///
    /// @return The package version.
    std::string get_version() const;

    /// @brief Retrieves the package release.
    ///
    /// @return The package release.
    std::string get_release() const;

    /// @brief Retrieves the package architecture.
    ///
    /// @return The package architecture.
    std::string get_arch() const;

    /// @brief Sets the package name.
    ///
    /// @param name The package name.
    void set_name(const std::string & name);

    /// @brief Sets the package epoch.
    ///
    /// @param epoch The package epoch.
    void set_epoch(const std::string & epoch);

    /// @brief Sets package version.
    ///
    /// @param version The package version.
    void set_version(const std::string & version);

    /// @brief Sets the package release.
    ///
    /// @param release The package release.
    void set_release(const std::string & release);

    /// @brief Sets the package architecture.
    ///
    /// @param arch The package architecture.
    void set_arch(const std::string & arch);

    /// @brief Converts the NEVRA object to its full string representation.
    ///
    /// @return The NEVRA string.
    std::string to_string() const;

private:
    friend class Package;

    class Impl;
    std::unique_ptr<Impl> p_impl;
};

}