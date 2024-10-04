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

    /// @brief Retrieves the root URL of the repository.
    /// @return The base URL.
    std::string get_url() const;

    /// @brief Sets the repository ID.
    /// @param url The repository ID to set.
    void set_id(const std::string & id);

    /// @brief Sets the root URL of the repository.
    /// @param url The URL to set.
    void set_url(const std::string & url);

private:
    friend class Package;
    friend class Repositories;

    class Impl;
    std::unique_ptr<Impl> p_impl;
};

}