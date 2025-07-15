// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "libpkgmanifest/common/exception.hpp"

namespace libpkgmanifest::common {

ParserError::ParserError(const std::string & message) : std::runtime_error(message) {}
SerializerError::SerializerError(const std::string & message) : std::runtime_error(message) {}

}