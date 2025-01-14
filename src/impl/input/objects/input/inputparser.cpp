#include "inputparser.hpp"

namespace libpkgmanifest::internal::input {

using namespace libpkgmanifest::internal::common;

InputParser::InputParser(
    std::unique_ptr<IInputFactory> input_factory,
    std::shared_ptr<IRepositoriesParser> repositories_parser,
    std::shared_ptr<IVersionParser> version_parser,
    std::shared_ptr<IPackagesParser> packages_parser,
    std::shared_ptr<IModulesParser> modules_parser,
    std::shared_ptr<IOptionsParser> options_parser,
    std::shared_ptr<IStringListParser> string_list_parser)
    : input_factory(std::move(input_factory))
    , repositories_parser(std::move(repositories_parser))
    , version_parser(std::move(version_parser))
    , packages_parser(std::move(packages_parser))
    , modules_parser(std::move(modules_parser))
    , options_parser(std::move(options_parser))
    , string_list_parser(std::move(string_list_parser)) {}

std::unique_ptr<IInput> InputParser::parse(const IYamlNode & node) const {
    auto input = input_factory->create();

    input->set_document(node.get("document")->as_string());
    input->set_version(version_parser->parse(*node.get("version")));
    input->set_repositories(repositories_parser->parse(*node.get("repositories")));
    input->set_packages(packages_parser->parse(*node.get("packages")));

    if (node.has("modules")) {
        input->set_modules(modules_parser->parse(*node.get("modules")));
    }

    for (auto & arch_node : node.get("archs")->as_list()) {
        input->get_archs().push_back(arch_node->as_string());
    }

    if (node.has("options")) {
        input->set_options(options_parser->parse(*node.get("options")));
    }

    return input;
}

}