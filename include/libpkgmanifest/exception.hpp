#pragma once

#include <stdexcept>
#include <string>

namespace libpkgmanifest {

/// @brief Exception thrown when there is an issue parsing the manifest file.
class ParserError : public std::runtime_error {
public:
    ParserError(const std::string & message);
};

/// @brief Exception thrown when serializing manifest objects to a file fails.
class SerializerError : public std::runtime_error {
public:
    SerializerError(const std::string & message);
};

}