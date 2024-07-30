#include "lockfile_impl.hpp"

#include "liblockfile/parser.hpp"

#include "liblockfile/wrappers/factory.hpp"

namespace liblockfile {

class Parser::Impl {
public:
    Impl() : parser(internal::Factory::create_parser()) {}
private:
    friend Parser;
    std::unique_ptr<internal::IParser> parser;
};

Parser::Parser() : p_impl(std::make_unique<Impl>()) {}

Parser::~Parser() = default;

LockFile Parser::parse(const std::string & path) const {
    LockFile file;
    file.p_impl->set(p_impl->parser->parse(path));
    return file;
}

}