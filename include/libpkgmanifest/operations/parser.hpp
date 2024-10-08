#pragma once

#include "libpkgmanifest/objects/manifest.hpp"

#include <memory>
#include <string>

namespace libpkgmanifest {

/// @brief A class responsible for parsing the manifest YAML file into objects.
class Parser {
public:
    Parser();
    ~Parser();

    /// @brief Parses the manifest file from a specified file path.
    /// @param path The location of the manifest file.
    /// @return A manifest object containing data parsed from the file.
    /// @throws ParserError if an error occurs during file parsing.
    Manifest parse(const std::string & path) const;

private:
    class Impl;
    std::unique_ptr<Impl> p_impl;
};

}