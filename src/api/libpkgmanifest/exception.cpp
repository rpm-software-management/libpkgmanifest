#include "libpkgmanifest/common/exception.hpp"

namespace libpkgmanifest {

ParserError::ParserError(const std::string & message) : std::runtime_error(message) {}
SerializerError::SerializerError(const std::string & message) : std::runtime_error(message) {}

}