#include "parser.hpp"

namespace liblockfile::internal {

Parser::Parser(std::unique_ptr<IYamlParser> yaml_parser, std::unique_ptr<ILockFileParser> file_parser)
    : yaml_parser(std::move(yaml_parser))
    , file_parser(std::move(file_parser)) {}

std::unique_ptr<ILockFile> Parser::parse(const std::string & path) const {
    auto node = yaml_parser->from_file(path);
    auto lock_file = file_parser->parse(*node);
    return lock_file;
}

}