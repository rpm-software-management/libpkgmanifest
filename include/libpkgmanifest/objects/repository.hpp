#pragma once

#include <memory>
#include <string>

namespace libpkgmanifest {

/// @brief Represents a single repository within the manifest.
class Repository {
public:
    Repository();
    ~Repository();

    Repository(const Repository & other);
    Repository & operator=(const Repository & other);

    Repository(Repository && other) noexcept;
    Repository & operator=(Repository && other) noexcept;

    /// @brief Retrieves the repository ID.
    /// @return The repository ID.
    std::string get_id() const;

    /// @brief Retrieves the base URL of the repository.
    /// @return The base URL.
    std::string get_baseurl() const;

    /// @brief Retrieves the metalink URL of the repository.
    /// @return The metalink URL.
    std::string get_metalink() const;

    /// @brief Retrieves the mirrorlist URL of the repository.
    /// @return The mirrorlist URL.
    std::string get_mirrorlist() const;

    /// @brief Sets the repository ID.
    /// @param id The repository ID to set.
    void set_id(const std::string & id);

    /// @brief Sets the base URL of the repository.
    /// @param baseurl The base URL to set.
    void set_baseurl(const std::string & baseurl);

    /// @brief Sets the metalink URL of the repository.
    /// @param metalink The metalink URL to set.
    void set_metalink(const std::string & metalink);

    /// @brief Sets the mirrorlist URL of the repository.
    /// @param mirrorlist The mirrorlist URL to set.
    void set_mirrorlist(const std::string & mirrorlist);

private:
    friend class Package;
    friend class Repositories;

    class Impl;
    std::unique_ptr<Impl> p_impl;
};

}