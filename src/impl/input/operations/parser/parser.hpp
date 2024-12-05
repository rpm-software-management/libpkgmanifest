#pragma once

#include "iparser.hpp"

#include "impl/common/yaml/iyamlparser.hpp"
#include "impl/input/objects/input/iinputparser.hpp"
#include "impl/input/operations/prototypefileconverter/iprototypefileconverter.hpp"

namespace libpkgmanifest::internal::input {

using namespace libpkgmanifest::internal::common;

class Parser : public IParser {
public:
    Parser(
        std::unique_ptr<IYamlParser> yaml_parser,
        std::unique_ptr<IInputParser> input_parser,
        std::unique_ptr<IPrototypeFileConverter> prototype_converter);

    virtual std::unique_ptr<IInput> parse(const std::string & path) const override;
    virtual std::unique_ptr<IInput> parse_from_prototype(const std::string & path) const override;

private:
    std::unique_ptr<IYamlParser> yaml_parser;
    std::unique_ptr<IInputParser> input_parser;
    std::unique_ptr<IPrototypeFileConverter> prototype_converter;
};

}