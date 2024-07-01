#include "versionparser.hpp"

namespace liblockfile {

VersionParser::VersionParser(
    const IVersionFactory & version_factory)
    : version_factory(version_factory) {}

std::unique_ptr<IVersionInternal> VersionParser::parse(const IYamlNode & node) const {
    auto version = version_factory.create();

    version->set_major(node.get("major")->as_uint());
    version->set_minor(node.get("minor")->as_uint());
    version->set_patch(node.get("patch")->as_uint());

    return version;
}

}