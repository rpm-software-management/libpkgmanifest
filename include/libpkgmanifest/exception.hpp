#pragma once

#include <stdexcept>
#include <string>

namespace libpkgmanifest {

class ParserError : public std::runtime_error {
public:
    ParserError(const std::string & message);
};

class SerializerError : public std::runtime_error {
public:
    SerializerError(const std::string & message);
};

}