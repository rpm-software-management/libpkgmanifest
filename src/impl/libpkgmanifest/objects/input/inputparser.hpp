#pragma once

#include "iinputfactory.hpp"
#include "iinputparser.hpp"

#include "impl/libpkgmanifest/objects/repositories/irepositoriesparser.hpp"
#include "impl/libpkgmanifest/objects/version/iversionparser.hpp"

namespace libpkgmanifest::internal {

class InputParser : public IInputParser {
public:
    InputParser(
        std::unique_ptr<IInputFactory> input_factory,
        std::shared_ptr<IRepositoriesParser> repositories_parser,
        std::shared_ptr<IVersionParser> version_parser);

    virtual std::unique_ptr<IInput> parse(const IYamlNode & node) const override;

private:
    std::unique_ptr<IInputFactory> input_factory;
    std::shared_ptr<IRepositoriesParser> repositories_parser;
    std::shared_ptr<IVersionParser> version_parser;
};

}