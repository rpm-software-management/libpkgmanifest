#include "versionparser.hpp"

namespace liblockfile {

VersionParser::VersionParser(
    std::unique_ptr<IVersionFactory> version_factory,
    std::shared_ptr<IStringSplitter> string_splitter)
    : version_factory(std::move(version_factory)) 
    , string_splitter(string_splitter) {}

std::unique_ptr<IVersionInternal> VersionParser::parse(const IYamlNode & node) const {
    // TODO: Handle invalid version parts number?
    // TODO: Handle invalid non-number version parts?
    auto version = version_factory->create();
    auto version_parts = string_splitter->split(node.as_string(), '.');

    if(version_parts.size() > 0) {
        version->set_major(std::stoul(version_parts[0]));
    }

    if(version_parts.size() > 1) {
        version->set_minor(std::stoul(version_parts[1]));
    }

    if(version_parts.size() > 2) {
        version->set_patch(std::stoul(version_parts[2]));
    }

    return version;
}

}