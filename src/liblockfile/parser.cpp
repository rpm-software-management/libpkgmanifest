#include "parser.hpp"

namespace liblockfile {

Parser::Parser(const IYamlParser & yaml_parser, const ILockFileParser & file_parser)
    : yaml_parser(yaml_parser)
    , file_parser(file_parser) {}

std::unique_ptr<ILockFile> Parser::parse(const std::string & path) const {
    auto node = yaml_parser.from_file(path);
    auto lock_file = file_parser.parse(*node);
    return lock_file;
}

}