// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "package.hpp"

#include <memory>
#include <string>
#include <vector>

namespace libpkgmanifest::manifest {

using namespace libpkgmanifest::common;

/// @brief A container for all packages listed in the manifest.
class Packages {
public:
    Packages();
    ~Packages();

    Packages(const Packages & other);
    Packages & operator=(const Packages & other);

    Packages(Packages && other) noexcept;
    Packages & operator=(Packages && other) noexcept;

    /// @brief Retrieves a list of all packages in the container.
    ///
    /// @return A vector containing all packages.
    std::vector<Package> get() const;

    /// @brief Retrieves a list of packages filtered by the specified base architecture.
    ///
    /// @param basearch The base architecture used to filter the packages.
    /// @param with_source True if source packages should be included in the result.
    /// @return A vector containing the packages for the specified base architecture.
    std::vector<Package> get(const std::string & basearch, bool with_source = false) const;

    /// @brief Adds a given package to the container.
    ///
    /// @note The package is categorized within the container based on its architecture.
    ///
    /// @param package The package to be added.
    void add(Package & package);

    /// @brief Adds a given package to the container and link it to the given base architecture.
    ///
    /// @note Used when storing multiple base architectures in a manifest file.
    ///
    /// @param package The package to be added.
    /// @param basearch The base architecture to link the package to.
    void add(Package & package, const std::string & basearch);

    /// @brief Verifies if the given package exists in the container.
    ///
    /// @note Packages are considered identical if they share the same NEVRA and repository ID.
    ///
    /// @return True if the package is present in the container.
    bool contains(const Package & package);

    /// @brief Binds the repositories to the packages object.
    ///
    /// @note Used to reference and validate repository-related information within the packages.
    ///
    /// @param repositories The repositories object to bind.
    void attach(Repositories & repositories);

private:
    friend class Manifest;

    class Impl;
    std::unique_ptr<Impl> p_impl;
};

}