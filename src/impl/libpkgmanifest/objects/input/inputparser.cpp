#include "inputparser.hpp"

namespace libpkgmanifest::internal {

InputParser::InputParser(
    std::unique_ptr<IInputFactory> input_factory,
    std::unique_ptr<IRepositoriesParser> repositories_parser,
    std::unique_ptr<IVersionParser> version_parser)
    : input_factory(std::move(input_factory))
    , repositories_parser(std::move(repositories_parser))
    , version_parser(std::move(version_parser)) {}

std::unique_ptr<IInput> InputParser::parse([[maybe_unused]] const IYamlNode & node) const {
    throw;
}

}