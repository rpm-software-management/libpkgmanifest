#pragma once

#include "repository.hpp"

#include <map>
#include <memory>
#include <string>

namespace libpkgmanifest {

/// @brief A container for all repositories listed in the manifest.
class Repositories {
public:
    Repositories();
    ~Repositories();

    Repositories(const Repositories & other);
    Repositories & operator=(const Repositories & other);

    Repositories(Repositories && other) noexcept;
    Repositories & operator=(Repositories && other) noexcept;

    /// @brief Retrieves all repositories by their IDs.
    /// @return A dictionary of repositories.
    std::map<std::string, Repository> get() const;

    /// @brief Retrieves a repository by its ID.
    /// @param id The repository ID.
    /// @return A repository with the given ID.
    Repository get(const std::string & id) const;

    /// @brief Adds a repository to the container.
    /// @param package The repository to add.
    void add(Repository & repository);

private:
    friend class Manifest;
    friend class Package;
    friend class Packages;

    class Impl;
    std::unique_ptr<Impl> p_impl;
};

}