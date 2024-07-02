#pragma once

#include "liblockfile/iparser.hpp"
#include "liblockfile/objects/lockfile/ilockfileparser.hpp"
#include "liblockfile/yaml/iyamlparser.hpp"

namespace liblockfile {

class Parser : IParser {
public:
    Parser(const IYamlParser & yaml_parser, const ILockFileParser & file_parser);

    virtual std::unique_ptr<ILockFile> parse(const std::string & path) const override;

private:
    const IYamlParser & yaml_parser;
    const ILockFileParser & file_parser;
};

}