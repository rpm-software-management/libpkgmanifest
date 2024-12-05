#pragma once

#include "input.hpp"

#include <memory>
#include <string>

namespace libpkgmanifest::input {

/// @brief A class responsible for parsing the YAML files into objects.
class Parser {
public:
    Parser();
    ~Parser();

    /// @brief Parses the input file from a specified file path.
    /// @param path The location of the input file.
    /// @return An input object containing data parsed from the file.
    /// @throws ParserError if an error occurs during file parsing.
    Input parse(const std::string & path) const;

    /// @brief Parses the input file in prototype format from a specified file path.
    /// @note This ensures compatibility with clients that have already deployed the existing prototype format.
    /// @param path The location of the input file.
    /// @return An input object containing data parsed from the file.
    /// @throws ParserError if an error occurs during file parsing.
    Input parse_prototype(const std::string & path) const;

private:
    class Impl;
    std::unique_ptr<Impl> p_impl;
};

}