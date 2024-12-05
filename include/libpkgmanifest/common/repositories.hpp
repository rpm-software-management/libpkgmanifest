#pragma once

#include "repository.hpp"

#include <memory>
#include <string>


namespace libpkgmanifest::input {
    class Input;
};


namespace libpkgmanifest::manifest {
    class Manifest;
    class Package;
    class Packages;
};


namespace libpkgmanifest::common {

class RepositoriesIterator;

/// @brief A container for all repositories listed in the manifest.
class Repositories {
public:
    Repositories();
    ~Repositories();

    Repositories(const Repositories & other);
    Repositories & operator=(const Repositories & other);

    Repositories(Repositories && other) noexcept;
    Repositories & operator=(Repositories && other) noexcept;

    /// @brief Checks if a given repository exists.
    /// @param id The repository ID.
    /// @return True if the given repository exists; otherwise, false.
    bool contains(const std::string & id) const;

    /// @brief Gets the number of repositories in the container.
    /// @return The size of the repositories container.
    std::size_t size() const;

    /// @brief Retrieves a repository by its ID.
    /// @param id The repository ID.
    /// @return A repository with the given ID.
    Repository get(const std::string & id) const;

    /// @brief Adds a repository to the container.
    /// @param repository The repository to add.
    void add(Repository & repository);

    /// @brief Implements the iteration API.
    RepositoriesIterator begin();
    RepositoriesIterator end();

private:
    friend class libpkgmanifest::input::Input;
    friend class libpkgmanifest::manifest::Manifest;
    friend class libpkgmanifest::manifest::Package;
    friend class libpkgmanifest::manifest::Packages;
    friend class RepositoriesIterator;

    class Impl;
    std::unique_ptr<Impl> p_impl;
};

class RepositoriesIterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = Repository;
    using pointer = void;
    using reference = Repository;

    RepositoriesIterator(Repositories * repositories);
    ~RepositoriesIterator();

    RepositoriesIterator(const RepositoriesIterator & other);
    RepositoriesIterator & operator=(const RepositoriesIterator & other);

    RepositoriesIterator(RepositoriesIterator && other) noexcept;
    RepositoriesIterator & operator=(RepositoriesIterator && other) noexcept;

    Repository operator*();
    RepositoriesIterator & operator++();
    bool operator!=(const RepositoriesIterator & other) const;

private:
    friend Repositories;

    class Impl;
    std::unique_ptr<Impl> p_impl;
};

}