#include "nevraparser.hpp"

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

NevraParseError::NevraParseError(const std::string & message)
    : std::runtime_error(message) {}

NevraParser::NevraParser(std::shared_ptr<INevraFactory> nevra_factory)
    : nevra_factory(std::move(nevra_factory)) {}

// TODO: Refactor to share the common evr logic

std::unique_ptr<INevra> NevraParser::parse(const IYamlNode & node) const {
    auto nevra = nevra_factory->create();
    auto nevra_string = node.as_string();

    // Find the architecture
    size_t last_dot_position = nevra_string.find_last_of('.');
    if (last_dot_position == std::string::npos) {
        throw NevraParseError("Failed to parse architecture from the nevra string: " + nevra_string);
    }
    nevra->set_arch(nevra_string.substr(last_dot_position + 1));

    // Find the release
    size_t last_dash_position = nevra_string.find_last_of('-');
    if (last_dash_position == std::string::npos || last_dash_position > last_dot_position) {
        throw NevraParseError("Failed to parse release from the nevra string: " + nevra_string);
    }
    nevra->set_release(nevra_string.substr(last_dash_position + 1, last_dot_position - last_dash_position - 1));

    // Find the second last dash separating the package name
    size_t second_last_dash_position = nevra_string.find_last_of('-', last_dash_position - 1);
    if (second_last_dash_position == std::string::npos) {
        throw NevraParseError("Failed to parse the nevra string: " + nevra_string);
    }

    // Find the (optional) epoch and based on that also the version
    size_t colon_position = nevra_string.find(':');
    if (colon_position != std::string::npos) {
        nevra->set_version(nevra_string.substr(colon_position + 1, last_dash_position - colon_position - 1));
        nevra->set_epoch(nevra_string.substr(second_last_dash_position + 1, colon_position - second_last_dash_position - 1));
    } else {
        nevra->set_version(nevra_string.substr(second_last_dash_position + 1, last_dash_position - second_last_dash_position - 1));
    }

    // Set the name
    nevra->set_name(nevra_string.substr(0, second_last_dash_position));

    return nevra;
}

std::unique_ptr<INevra> NevraParser::parse(const std::string & name, const std::string & arch, const IYamlNode & node) const {
    auto nevra = nevra_factory->create();
    auto evr_string = node.as_string();

    nevra->set_name(name);
    nevra->set_arch(arch);

    // Find the release
    size_t last_dash_position = evr_string.find_last_of('-');
    if (last_dash_position == std::string::npos) {
        throw NevraParseError("Failed to parse release from the evr string: " + evr_string);
    }
    nevra->set_release(evr_string.substr(last_dash_position + 1));

    // Find the (optional) epoch and based on that also the version
    size_t colon_position = evr_string.find(':');
    if (colon_position != std::string::npos) {
        nevra->set_version(evr_string.substr(colon_position + 1, last_dash_position - colon_position - 1));
        nevra->set_epoch(evr_string.substr(0, colon_position));
    } else {
        nevra->set_version(evr_string.substr(0, last_dash_position));
    }

    return nevra;
}

}