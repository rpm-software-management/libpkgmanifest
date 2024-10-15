#pragma once

#include "packages.hpp"
#include "repositories.hpp"
#include "version.hpp"

#include <memory>
#include <string>

namespace libpkgmanifest {

/// @brief The primary data class that stores all information related to the items in the manifest file.
class Manifest {
public:
    Manifest();
    ~Manifest();

    Manifest(const Manifest & other);
    Manifest & operator=(const Manifest & other);

    Manifest(Manifest && other) noexcept;
    Manifest & operator=(Manifest && other) noexcept;

    /// @brief Retrieves the YAML document identifier.
    /// @note This is expected to be the value "rpm-package-manifest".
    /// @return The document identifier.
    std::string get_document() const;

    /// @brief Retrieves the version of the YAML document.
    /// @note This version changes if the structure or format of the document's properties has been updated.
    /// @return The document version.
    Version & get_version();

    /// @brief Retrieves a structure containing all the packages defined in the manifest file.
    /// @return A structure with the packages listed in the manifest.
    Packages & get_packages();

    /// @brief Retrieves a structure containing all the repositories defined in the manifest file.
    /// @return A structure with the repositories listed in the manifest.
    Repositories & get_repositories();

    /// @brief Sets the YAML document identifier.
    /// @param document The YAML identifier to set.
    void set_document(const std::string & document);

    /// @brief Sets the version of the YAML document.
    /// @param version The version to set for the document.
    void set_version(Version & version);

    /// @brief Assigns a structure with all the packages to be included in the manifest file.
    /// @param packages A structure containing the packages to be set.
    void set_packages(Packages & packages);

    /// @brief Assigns a structure with all the repositories to be included in the manifest file.
    /// @param repositories A structure containing the repositories to be set.
    void set_repositories(Repositories & repositories);

private:
    friend class Parser;
    friend class Serializer;

    class Impl;
    std::unique_ptr<Impl> p_impl;
};

}