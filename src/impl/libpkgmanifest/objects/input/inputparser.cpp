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

    auto packages = node.get("packages");
    if (packages->has("install")) {
        std::vector<std::string> install_packages;
        for (auto & package_node : packages->get("install")->as_list()) {
            install_packages.push_back(package_node->as_string());
        }
        input->get_packages()["install"] = std::move(install_packages);
    }
    if (packages->has("reinstall")) {
        std::vector<std::string> reinstall_packages;
        for (auto & package_node : packages->get("reinstall")->as_list()) {
            reinstall_packages.push_back(package_node->as_string());
        }
        input->get_packages()["reinstall"] = std::move(reinstall_packages);
    }

    if (node.has("modules")) {
        auto modules = node.get("modules");
        if (modules->has("enable")) {
            std::vector<std::string> enable_modules;
            for (auto & module_node : modules->get("enable")->as_list()) {
                enable_modules.push_back(module_node->as_string());
            }
            input->get_modules()["enable"] = std::move(enable_modules);
        }
    }

    for (auto & arch_node : node.get("archs")->as_list()) {
        input->get_archs().push_back(arch_node->as_string());
    }

    if (node.has("options")) {
        auto options = node.get("options");
        if (options->has("allow_erasing")) {
            input->set_allow_erasing(options->get("allow_erasing")->as_bool());
        }
    }

    return input;
}

}