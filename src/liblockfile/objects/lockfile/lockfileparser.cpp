#include "lockfileparser.hpp"

namespace liblockfile {

LockFileParser::LockFileParser(
    std::unique_ptr<ILockFileFactory> file_factory,
    std::unique_ptr<IPackagesParser> packages_parser, 
    std::unique_ptr<IVersionParser> version_parser)
    : file_factory(std::move(file_factory))
    , packages_parser(std::move(packages_parser))
    , version_parser(std::move(version_parser)) {}

std::unique_ptr<ILockFileInternal> LockFileParser::parse(const IYamlNode & node) const {
    auto file = file_factory->create();

    file->set_document(node.get("document")->as_string());
    file->set_version(version_parser->parse(*node.get("version")));
    file->set_packages(packages_parser->parse(*node.get("data")->get("packages")));

    return file;
}

}