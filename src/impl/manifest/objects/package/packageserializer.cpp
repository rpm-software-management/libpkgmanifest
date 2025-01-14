#include "packageserializer.hpp"

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

PackageSerializer::PackageSerializer(
    std::shared_ptr<IYamlNodeFactory> node_factory,
    std::unique_ptr<IChecksumSerializer> checksum_serializer,
    std::unique_ptr<IModuleSerializer> module_serializer)
    : node_factory(std::move(node_factory))
    , checksum_serializer(std::move(checksum_serializer))
    , module_serializer(std::move(module_serializer)) {}

std::unique_ptr<IYamlNode> PackageSerializer::serialize(const IPackage & package) const {
    auto node = node_factory->create();

    auto & nevra = package.get_nevra();

    auto name_node = node_factory->create();
    name_node->set(nevra.get_name());
    node->insert("name", std::move(name_node));

    auto repo_id_node = node_factory->create();
    repo_id_node->set(package.get_repo_id());
    node->insert("repo_id", std::move(repo_id_node));

    auto location = package.get_location();
    if (!location.empty()) {
        auto location_node = node_factory->create();
        location_node->set(location);
        node->insert("location", std::move(location_node));
    }

    node->insert("checksum", checksum_serializer->serialize(package.get_checksum()));

    auto size_node = node_factory->create();
    size_node->set(package.get_size());
    node->insert("size", std::move(size_node));

    auto evr_node = node_factory->create();
    evr_node->set(nevra.to_evr_string());
    node->insert("evr", std::move(evr_node));

    auto & srpm = package.get_srpm();
    if (!srpm.get_name().empty()) {
        auto srpm_node = node_factory->create();
        srpm_node->set(srpm.to_string());
        node->insert("srpm", std::move(srpm_node));
    }

    auto & module = package.get_module();
    if (!module.get_name().empty()) {
        node->insert("module", module_serializer->serialize(module));
    }

    return node;
}

}