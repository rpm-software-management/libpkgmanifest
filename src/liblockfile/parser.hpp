#pragma once

#include "liblockfile/iparser.hpp"
#include "liblockfile/objects/lockfile/ilockfileparser.hpp"
#include "liblockfile/yaml/iyamlparser.hpp"

namespace liblockfile {

class Parser : public IParser {
public:
    Parser(std::unique_ptr<IYamlParser> yaml_parser, std::unique_ptr<ILockFileParser> file_parser);

    virtual std::unique_ptr<ILockFile> parse(const std::string & path) const override;

private:
    std::unique_ptr<IYamlParser> yaml_parser;
    std::unique_ptr<ILockFileParser> file_parser;
};

}