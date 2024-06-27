#include "parser.hpp"

namespace liblockfile {

Parser::Parser(IYamlParser & yaml_parser)
    : yaml_parser(yaml_parser) {}

std::unique_ptr<ILockFile> Parser::parse([[maybe_unused]] const std::string & path) const {
    throw; // TODO
}

}