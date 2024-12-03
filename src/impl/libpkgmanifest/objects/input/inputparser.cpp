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

    auto packages_map = node.get("packages")->as_map();
    if (packages_map.contains("install")) {
        std::vector<std::string> install_packages;
        for (auto & package_node : packages_map["install"]->as_list()) {
            install_packages.push_back(package_node->as_string());
        }
        input->get_packages()["install"] = std::move(install_packages);
    }
    if (packages_map.contains("reinstall")) {
        std::vector<std::string> reinstall_packages;
        for (auto & package_node : packages_map["reinstall"]->as_list()) {
            reinstall_packages.push_back(package_node->as_string());
        }
        input->get_packages()["reinstall"] = std::move(reinstall_packages);
    }

    auto modules_map = node.get("modules")->as_map();
    if (modules_map.contains("enable")) {
        std::vector<std::string> enable_modules;
        for (auto & module_node : modules_map["enable"]->as_list()) {
            enable_modules.push_back(module_node->as_string());
        }
        input->get_modules()["enable"] = std::move(enable_modules);
    }

    for (auto & arch_node : node.get("archs")->as_list()) {
        input->get_archs().push_back(arch_node->as_string());
    }

    return input;
}

}