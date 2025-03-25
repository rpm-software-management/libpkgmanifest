#pragma once

#include <memory>
#include <string>
#include <vector>

namespace libpkgmanifest::input {

/// @brief A container with input packages and their associated actions.
class Packages {
public:
    Packages();
    ~Packages();

    Packages(const Packages & other);
    Packages & operator=(const Packages & other);

    Packages(Packages && other) noexcept;
    Packages & operator=(Packages && other) noexcept;

    /// @brief Retrieves a list of packages designated for installation when resolving manifest content.
    ///
    /// @return A vector containing installation packages.
    std::vector<std::string> & get_installs();

    /// @brief Retrieves a list of packages designated for reinstallation when resolving manifest content.
    ///
    /// @return A vector containing reinstallation packages.
    std::vector<std::string> & get_reinstalls();

private:
    friend class Input;

    class Impl;
    std::unique_ptr<Impl> p_impl;
};

}