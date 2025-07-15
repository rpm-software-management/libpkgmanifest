// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "stringsplitter.hpp"

#include <iostream>
#include <sstream>

namespace libpkgmanifest::internal::common {

std::vector<std::string> StringSplitter::split(const std::string & string, char delimiter) const {
    std::vector<std::string> parts;
    std::stringstream stream(string);
    std::string part;

    while (std::getline(stream, part, delimiter)) {
        parts.push_back(part);
    }

    return parts;
}

}