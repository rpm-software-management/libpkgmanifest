#pragma once

#include <memory>


namespace libpkgmanifest::input {
    class Input;
};


namespace libpkgmanifest::manifest {
    class Manifest;
};


namespace libpkgmanifest::common {

/// @brief Structure representing a version, supporting up to three components.
class Version {
public:
    Version();
    ~Version();

    Version(const Version & other);
    Version & operator=(const Version & other);

    Version(Version && other) noexcept;
    Version & operator=(Version && other) noexcept;

    /// @brief Retrieves the major version component.
    /// @return The major version number.
    unsigned get_major() const;

    /// @brief Retrieves the minor version component.
    /// @return The minor version number.
    unsigned get_minor() const;

    /// @brief Retrieves the patch version component.
    /// @return The patch version number.
    unsigned get_patch() const;

    /// @brief Sets the major version component.
    /// @param major The value of the major version component.
    void set_major(unsigned major);

    /// @brief Sets the minor version component.
    /// @param minor The value for the minor version component.
    void set_minor(unsigned minor);

    /// @brief Sets the patch version component.
    /// @param patch The value for the patch version component.
    void set_patch(unsigned patch);

private:
    friend class libpkgmanifest::input::Input;
    friend class libpkgmanifest::manifest::Manifest;

    class Impl;
    std::unique_ptr<Impl> p_impl;
};

}