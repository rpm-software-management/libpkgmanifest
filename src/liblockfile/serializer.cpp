#include "serializer.hpp"

namespace liblockfile {

Serializer::Serializer(std::unique_ptr<IYamlSerializer> yaml_serializer, std::unique_ptr<ILockFileSerializer> file_serializer)
    : yaml_serializer(std::move(yaml_serializer))
    , file_serializer(std::move(file_serializer)) {}

void Serializer::serialize(const ILockFile & file, const std::string & path) const {
    auto node = file_serializer->serialize(file);
    yaml_serializer->to_file(*node, path);
}

}