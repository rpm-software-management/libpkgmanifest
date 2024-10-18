#pragma once

#include "libpkgmanifest/objects/input.hpp"
#include "libpkgmanifest/objects/manifest.hpp"

#include <memory>
#include <string>

namespace libpkgmanifest {

/// @brief A class responsible for parsing the YAML files into objects.
class Parser {
public:
    Parser();
    ~Parser();

    /// @brief Parses the manifest file from a specified file path.
    /// @param path The location of the manifest file.
    /// @return A manifest object containing data parsed from the file.
    /// @throws ParserError if an error occurs during file parsing.
    Manifest parse_manifest(const std::string & path) const;

    /// @brief Parses the input file from a specified file path.
    /// @param path The location of the input file.
    /// @return An input object containing data parsed from the file.
    /// @throws ParserError if an error occurs during file parsing.
    Input parse_input(const std::string & path) const;

    /// @brief Parses the input file in prototype format from a specified file path.
    /// @note This ensures compatibility with clients that have already deployed the existing prototype format.
    /// @param path The location of the input file.
    /// @return An input object containing data parsed from the file.
    /// @throws ParserError if an error occurs during file parsing.
    Input parse_prototype_input(const std::string & path) const;

private:
    class Impl;
    std::unique_ptr<Impl> p_impl;
};

}