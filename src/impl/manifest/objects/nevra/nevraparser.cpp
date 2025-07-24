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

namespace {
    void splitEVRA(std::unique_ptr<INevra> & nevra, const std::string & evr_string, bool extract_arch = true) {
        rpmver evr = NULL;
        const char *e = NULL;
        const char *v = NULL;
        const char *r = NULL;
        std::string val;
        std::string arch;
        size_t last_dot_position;

        last_dot_position = evr_string.find_last_of('.');

        if (extract_arch && last_dot_position != std::string::npos) {
            arch = evr_string.substr(last_dot_position + 1);
            nevra->set_arch(arch);
            evr = rpmverParse(evr_string.substr(0, last_dot_position).c_str());
        } else {
            evr = rpmverParse(evr_string.c_str());
        }

        if (evr == NULL) {
            throw NevraParseError("Failed to parse epoch:version-release substring: " + evr_string);
        }

        try {
            // collect the components
            e = rpmverE(evr);
            v = rpmverV(evr);
            r = rpmverR(evr);

            // a NULL epoch is ok, but we at least need version and release
            if (v == NULL || r == NULL) {
                throw NevraParseError("Failed to parse epoch:version-release substring: " + evr_string);
            }

            // save the EVR components
            if (e != NULL) {
                val = e;
                nevra->set_epoch(val);
            }

            val = v;
            nevra->set_version(val);

            val = r;
            nevra->set_release(val);

            // cleanup
            rpmverFree(evr);
        } catch(...) {
            rpmverFree(evr);
            throw;
        }

        return;
    }
}

std::unique_ptr<INevra> NevraParser::parse(const IYamlNode & node) const {
    auto nevra = nevra_factory->create();
    auto nevra_string = node.as_string();

    // Positions within the substring
    size_t last_dash_position = nevra_string.find_last_of('-');

    // Validate that we have at least one hyphen
    if (last_dash_position == std::string::npos) {
        throw NevraParseError("Invalid NEVRA format - need at least one hyphen: " + nevra_string);
    }

    size_t second_last_dash_position = nevra_string.find_last_of('-', last_dash_position - 1);

    // Validate that we have at least two hyphens for name-version-release.arch format
    if (second_last_dash_position == std::string::npos) {
        throw NevraParseError("Invalid NEVRA format - at least two hyphens needed for name-version-release.arch: " + nevra_string);
    }

    // Get the EVR substring
    auto evr_string = nevra_string.substr(second_last_dash_position + 1);

    // Extract the epoch, version, release, and architecture
    splitEVRA(nevra, evr_string);

    // Set the name
    nevra->set_name(nevra_string.substr(0, second_last_dash_position));

    return nevra;
}

std::unique_ptr<INevra> NevraParser::parse(const std::string & name, const std::string & arch, const IYamlNode & node) const {
    auto nevra = nevra_factory->create();
    auto evr_string = node.as_string();

    nevra->set_name(name);
    nevra->set_arch(arch);
    splitEVRA(nevra, evr_string, false);

    return nevra;
}

}
