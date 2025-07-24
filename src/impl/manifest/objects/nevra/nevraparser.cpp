// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include <rpm/rpmver.h>
#include "nevraparser.hpp"

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

NevraParseError::NevraParseError(const std::string & message)
    : std::runtime_error(message) {}

NevraParser::NevraParser(std::shared_ptr<INevraFactory> nevra_factory)
    : nevra_factory(std::move(nevra_factory)) {}

static void splitEVR(std::unique_ptr<INevra> & nevra, const std::string & evr_string) {
    rpmver evr = NULL;
    const char *s = NULL;
    std::string val;

    // split up the epoch:version-release substring the librpm way
    evr = rpmverParse(evr_string.c_str());

    if (evr == NULL) {
        throw NevraParseError("Failed to parse epoch:version-release substring: " + evr_string);
    }

    // collect the components
    s = rpmverE(evr);

    if (s != NULL) {
        val = s;
        nevra->set_epoch(val);
    }

    s = rpmverV(evr);

    if (s != NULL) {
        val = s;
        nevra->set_version(val);
    }

    s = rpmverR(evr);

    if (s != NULL) {
        val = s;
        nevra->set_release(val);
    }

    // cleanup
    rpmverFree(evr);

    return;
}

std::unique_ptr<INevra> NevraParser::parse(const IYamlNode & node) const {
    auto nevra = nevra_factory->create();
    auto nevra_string = node.as_string();

    // Positions within the substring
    size_t last_dot_position = nevra_string.find_last_of('.');
    size_t last_dash_position = nevra_string.find_last_of('-');
    size_t second_last_dash_position = nevra_string.find_last_of('-', last_dash_position - 1);

    // Find the architecture
    if (last_dot_position == std::string::npos) {
        throw NevraParseError("Failed to parse architecture from the nevra string: " + nevra_string);
    }

    nevra->set_arch(nevra_string.substr(last_dot_position + 1));

    // Get the EVR substring
    auto evr_string = nevra_string.substr(second_last_dash_position + 1, last_dot_position - 1);

    // Extract the epoch, version, and release
    splitEVR(nevra, evr_string);

    // Set the name
    nevra->set_name(nevra_string.substr(0, second_last_dash_position));

    return nevra;
}

std::unique_ptr<INevra> NevraParser::parse(const std::string & name, const std::string & arch, const IYamlNode & node) const {
    auto nevra = nevra_factory->create();
    auto evr_string = node.as_string();

    nevra->set_name(name);
    nevra->set_arch(arch);
    splitEVR(nevra, evr_string);

    return nevra;
}

}
