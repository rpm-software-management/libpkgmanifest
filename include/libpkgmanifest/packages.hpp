#pragma once

#include "package.hpp"

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace libpkgmanifest {

/// @brief A container for all packages listed in the manifest.
class Packages {
public:
    Packages();
    ~Packages();

    Packages(const Packages & other);
    Packages & operator=(const Packages & other);

    Packages(Packages && other) noexcept;
    Packages & operator=(Packages && other) noexcept;

    /// @brief Retrieves all packages organized by architecture in a dictionary format.
    /// @note The key is the architecture, and the value is a list of packages defined in the manifest for that architecture.
    /// @return A dictionary with packages.
    std::map<std::string, std::vector<Package>> get() const;

    /// @brief Retrieves a list of packages filtered by the specified architecture.
    /// @param arch The architecture used to filter the packages.
    /// @return A vector containing the packages for the specified architecture.
    std::vector<Package> get(const std::string & arch) const;

    /// @brief Adds a given package to the container.
    /// @note The package is categorized within the container based on its architecture.
    /// @param package The package to be added.
    void add(Package & package);

    /// @brief Binds the repositories to the packages object.
    /// @note Used to reference and validate repository-related information within the packages.
    /// @param repositories The repositories object to bind.
    void attach(Repositories & repositories);

private:
    friend class Manifest;

    class Impl;
    std::unique_ptr<Impl> p_impl;
};

}