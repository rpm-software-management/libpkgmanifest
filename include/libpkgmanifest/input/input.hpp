#pragma once

#include "modules.hpp"
#include "options.hpp"
#include "packages.hpp"

#include "libpkgmanifest/common/repositories.hpp"
#include "libpkgmanifest/common/version.hpp"

#include <memory>
#include <string>
#include <vector>

namespace libpkgmanifest::input {

using namespace libpkgmanifest::common;

/// @brief Stores all information related to the items defined in the input file.
///
/// @note The file serves as input data for clients generating the manifest.
class Input {
public:
    Input();
    ~Input();

    Input(const Input & other);
    Input & operator=(const Input & other);

    Input(Input && other) noexcept;
    Input & operator=(Input && other) noexcept;

    /// @brief Retrieves the YAML document identifier.
    ///
    /// @note This is expected to be the value "rpm-package-input".
    ///
    /// @return The document identifier.
    std::string get_document() const;

    /// @brief Retrieves the version of the YAML document.
    ///
    /// @note This version changes if the structure or format of the document's properties has been updated.
    ///
    /// @return The document version.
    Version & get_version();

    /// @brief Retrieves a structure containing all repositories defined in the input file.
    ///
    /// @return A structure with the repositories listed in the input.
    Repositories & get_repositories();

    /// @brief Retrieves a structure containing all packages and their associated actions from the input file.
    ///
    /// @return A structure with the packages listed in the input.
    Packages & get_packages();

    /// @brief Retrieves a structure containing all the modules and their associated actions from the input file.
    ///
    /// @return A structure with the modules listed in the input.
    Modules & get_modules();

    /// @brief Retrieves a list of architectures from the input file.
    ///
    /// @return A list of architectures.
    std::vector<std::string> & get_archs();

    /// @brief Retrieves a structure containing options to override the default package manager behavior.
    ///
    /// @return A structure with the options listed in the input.
    Options & get_options();

    /// @brief Sets the YAML document identifier.
    ///
    /// @param document The YAML identifier to set.
    void set_document(const std::string & document);

    /// @brief Sets the version of the YAML document.
    ///
    /// @param version The version to set for the document.
    void set_version(Version & version);

    /// @brief Sets the repositories to be included in the input file.
    ///
    /// @param repositories A structure containing the repositories to set.
    void set_repositories(Repositories & repositories);

    /// @brief Sets the packages to be included in the input file.
    ///
    /// @param packages A structure containing the packages to set.
    void set_packages(Packages & packages);

    /// @brief Sets the modules to be included in the input file.
    ///
    /// @param modules A structure containing the modules to set.
    void set_modules(Modules & modules);

    /// @brief Sets the options to be included in the input file.
    ///
    /// @param options A structure containing the options to set.
    void set_options(Options & options);

private:
    friend class Parser;

    class Impl;
    std::unique_ptr<Impl> p_impl;
};

}