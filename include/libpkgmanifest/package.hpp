#pragma once

#include "checksum.hpp"
#include "module.hpp"
#include "nevra.hpp"
#include "repository.hpp"
#include "repositories.hpp"

#include <memory>
#include <stdint.h>
#include <string>

namespace libpkgmanifest {

/// @brief Represents a single package within the manifest.
class Package {
public:
    Package();
    ~Package();

    Package(const Package & other);
    Package & operator=(const Package & other);

    Package(Package && other) noexcept;
    Package & operator=(Package && other) noexcept;

    /// @brief Retrieves the repository identifier the packages is from.
    /// @return The repository ID.
    std::string get_repo_id() const;

    /// @brief Retrieves the package's relative path within the repository.
    /// @return The package's relative path.
    std::string get_location() const;

    /// @brief Retrieves the complete URL for downloading the package.
    /// @note Constructed by combining the repository URL and the package's relative location path.
    /// @return The full URL of the package.
    std::string get_url() const;

    /// @brief Retrieves the download size of the package in bytes.
    /// @return The size of the package in bytes.
    uint64_t get_size() const;

    /// @brief Retrieves the repository where the package originates.
    /// @return The repository object.
    Repository & get_repository() const;

    /// @brief Retrieves the checksum associated with this package.
    /// @return The package checksum.
    Checksum & get_checksum();

    /// @brief Retrieves the NEVRA package identifier.
    /// @return The NEVRA identifier of the package.
    Nevra & get_nevra();

    /// @brief Retrieves the NEVRA identifier of the source package.
    /// @note This identifies the source package used to build this binary package.
    /// @return The NEVRA identifier of the source package.
    Nevra & get_srpm();

    /// @brief Retrieves the module information associated with this package.
    /// @return The package module.
    Module & get_module();

    /// @brief Sets the repository identifier the package is from.
    /// @param repo_id The repository ID to be set.
    void set_repo_id(const std::string & repo_id);

    /// @brief Sets the package's relative path within the repository.
    /// @param url The path to be set for the package.
    void set_location(const std::string & location);

    /// @brief Sets the download size of the package in bytes.
    /// @param size The size of the package in bytes to be set.
    void set_size(uint64_t size);

    /// @brief Sets the checksum associated with this package.
    /// @param checksum The checksum to be set for the package.
    void set_checksum(Checksum & checksum);

    /// @brief Sets the package NEVRA identifier.
    /// @param nevra The NEVRA identifier to be set for the package.
    void set_nevra(Nevra & nevra);

    /// @brief Sets the source package NEVRA identifier.
    /// @note This identifies the source package used to build this binary package.
    void set_srpm(Nevra & srpm);

    /// @brief Sets the module information associated with this package.
    /// @param module The module to be set for the package.
    void set_module(Module & module);

    /// @brief Binds the repositories to the package object.
    /// @note Used to reference and validate repository-related information within the package.
    /// @param repositories The repositories object to bind.
    void attach(Repositories & repositories);

private:
    friend class Packages;

    class Impl;
    std::unique_ptr<Impl> p_impl;
};

}