#include "inputparser.hpp"

namespace libpkgmanifest::internal {

InputParser::InputParser(
    std::unique_ptr<IInputFactory> input_factory,
    std::shared_ptr<IRepositoriesParser> repositories_parser,
    std::shared_ptr<IVersionParser> version_parser)
    : input_factory(std::move(input_factory))
    , repositories_parser(repositories_parser)
    , version_parser(version_parser) {}

std::unique_ptr<IInput> InputParser::parse(const IYamlNode & node) const {
    auto input = input_factory->create();

    input->set_document(node.get("document")->as_string());
    input->set_version(version_parser->parse(*node.get("version")));
    input->set_repositories(repositories_parser->parse(*node.get("repositories")));

    for (auto & package_node : node.get("packages")->as_list()) {
        input->get_packages().push_back(package_node->as_string());
    }

    for (auto & arch_node : node.get("archs")->as_list()) {
        input->get_archs().push_back(arch_node->as_string());
    }

    return input;
}

}