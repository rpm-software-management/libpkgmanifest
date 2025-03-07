#include "versionparser.hpp"

namespace libpkgmanifest::internal::common {

VersionFormatError::VersionFormatError(const std::string & message) : std::runtime_error(message) {}

VersionParser::VersionParser(
    std::shared_ptr<IVersionFactory> version_factory,
    std::shared_ptr<IStringSplitter> string_splitter)
    : version_factory(std::move(version_factory))
    , string_splitter(std::move(string_splitter)) {}

std::unique_ptr<IVersion> VersionParser::parse(const IYamlNode & node) const {
    // TODO(jkolarik): Handle invalid version parts number?
    auto version = version_factory->create();
    auto version_string = node.as_string();
    auto version_parts = string_splitter->split(version_string, '.');

    try {
        if(version_parts.size() > 0) {
            version->set_major(std::stoul(version_parts[0]));
        }
    
        if(version_parts.size() > 1) {
            version->set_minor(std::stoul(version_parts[1]));
        }
    
        if(version_parts.size() > 2) {
            version->set_patch(std::stoul(version_parts[2]));
        }
    } catch (const std::invalid_argument &) {
        throw VersionFormatError("Version parts must be numbers: " + version_string);
    }

    return version;
}

}