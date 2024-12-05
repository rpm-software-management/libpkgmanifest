#include "prototypefileconverter.hpp"

#include <format>

namespace libpkgmanifest::internal::input {

using namespace libpkgmanifest::internal::common;

PrototypeFileConverter::PrototypeFileConverter(
    std::shared_ptr<IYamlNodeFactory> node_factory)
    : node_factory(node_factory) {}

std::unique_ptr<IYamlNode> PrototypeFileConverter::convert(const IYamlNode & node) const {
    auto result = node_factory->create();

    auto document_node = node_factory->create();
    document_node->set(INPUT_PROTOTYPE_DOCUMENT_ID);
    result->insert("document", std::move(document_node));

    auto version_node = node_factory->create();
    version_node->set(std::format("{}.{}.{}",
        INPUT_PROTOTYPE_DOCUMENT_VERSION_MAJOR,
        INPUT_PROTOTYPE_DOCUMENT_VERSION_MINOR,
        INPUT_PROTOTYPE_DOCUMENT_VERSION_PATCH));
    result->insert("version", std::move(version_node));

    auto result_repositories_node = node_factory->create();
    auto repositories_node = node.get("contentOrigin")->get("repos");
    for (auto & repository_node : repositories_node->as_list()) {
        auto result_repository_node = node_factory->create();
        result_repository_node->insert("id", repository_node->get("repoid"));
        result_repository_node->insert("baseurl", repository_node->get("baseurl"));
        result_repositories_node->add(std::move(result_repository_node));
    }
    result->insert("repositories", std::move(result_repositories_node));
    
    auto result_packages_node = node_factory->create();

    if (node.has("packages")) {
        auto result_install_packages_node = node_factory->create();
        auto packages_node = node.get("packages");
        for (auto & package_node : packages_node->as_list()) {
            // we just want to include package name string nodes
            if (package_node->has("arches")) {
                continue;
            }

            result_install_packages_node->add(std::move(package_node));
        }
        result_packages_node->insert("install", std::move(result_install_packages_node));
    }

    if (node.has("reinstallPackages")) {
        auto result_reinstall_packages_node = node_factory->create();
        auto packages_node = node.get("reinstallPackages");
        for (auto & package_node : packages_node->as_list()) {
            // we just want to include package name string nodes
            if (package_node->has("arches")) {
                continue;
            }

            result_reinstall_packages_node->add(std::move(package_node));
        }
        result_packages_node->insert("reinstall", std::move(result_reinstall_packages_node));
    }

    result->insert("packages", std::move(result_packages_node));

    auto result_modules_node = node_factory->create();

    if (node.has("moduleEnable")) {
        auto result_enable_modules_node = node_factory->create();
        auto modules_node = node.get("moduleEnable");
        for (auto & module_node : modules_node->as_list()) {
            // we just want to include module name string nodes
            if (module_node->has("arches")) {
                continue;
            }

            result_enable_modules_node->add(std::move(module_node));
        }
        result_modules_node->insert("enable", std::move(result_enable_modules_node));
    }

    result->insert("modules", std::move(result_modules_node));

    result->insert("archs", node.get("arches"));

    if (node.has("allowerasing")) {
        auto options_node = node_factory->create();
        options_node->insert("allow_erasing", node.get("allowerasing"));
        result->insert("options", std::move(options_node));
    }

    return result;
}

}