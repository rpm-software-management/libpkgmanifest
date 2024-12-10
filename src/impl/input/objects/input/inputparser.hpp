#pragma once

#include "iinputfactory.hpp"
#include "iinputparser.hpp"

#include "impl/common/objects/repositories/irepositoriesparser.hpp"
#include "impl/common/objects/version/iversionparser.hpp"
#include "impl/common/operations/stringlistparser/istringlistparser.hpp"
#include "impl/input/objects/modules/imodulesparser.hpp"
#include "impl/input/objects/options/ioptionsparser.hpp"
#include "impl/input/objects/packages/ipackagesparser.hpp"

namespace libpkgmanifest::internal::input {

using namespace libpkgmanifest::internal::common;

class InputParser : public IInputParser {
public:
    InputParser(
        std::unique_ptr<IInputFactory> input_factory,
        std::shared_ptr<IRepositoriesParser> repositories_parser,
        std::shared_ptr<IVersionParser> version_parser,
        std::shared_ptr<IPackagesParser> packages_parser,
        std::shared_ptr<IModulesParser> modules_parser,
        std::shared_ptr<IOptionsParser> options_parser,
        std::shared_ptr<IStringListParser> string_list_parser);

    virtual std::unique_ptr<IInput> parse(const IYamlNode & node) const override;

private:
    std::unique_ptr<IInputFactory> input_factory;
    std::shared_ptr<IRepositoriesParser> repositories_parser;
    std::shared_ptr<IVersionParser> version_parser;
    std::shared_ptr<IPackagesParser> packages_parser;
    std::shared_ptr<IModulesParser> modules_parser;
    std::shared_ptr<IOptionsParser> options_parser;
    std::shared_ptr<IStringListParser> string_list_parser;
};

}