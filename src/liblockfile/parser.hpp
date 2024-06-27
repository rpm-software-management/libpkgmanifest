#pragma once

#include "liblockfile/iparser.hpp"
#include "liblockfile/yaml/iyamlparser.hpp"

namespace liblockfile {

class Parser : IParser {
public:
    Parser(IYamlParser & yaml_parser);

    virtual std::unique_ptr<ILockFile> parse(const std::string & path) const override;

private:
    IYamlParser & yaml_parser;
};

}