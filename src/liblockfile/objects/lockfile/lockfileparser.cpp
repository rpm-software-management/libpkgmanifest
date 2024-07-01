#include "lockfileparser.hpp"

namespace liblockfile {

LockFileParser::LockFileParser(
    const ILockFileFactory & file_factory,
    const IPackagesParser & packages_parser, 
    const IVersionParser & version_parser)
    : file_factory(file_factory)
    , packages_parser(packages_parser)
    , version_parser(version_parser) {}

std::unique_ptr<ILockFileInternal> LockFileParser::parse(const IYamlNode & node) const {
    auto file = file_factory.create();

    file->set_document(node.get("document")->as_string());
    file->set_version(version_parser.parse(node));
    file->set_packages(packages_parser.parse(*node.get("data")->get("packages")));

    return file;
}

}