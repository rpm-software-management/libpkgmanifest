#pragma once

#include "liblockfile/iserializer.hpp"
#include "liblockfile/objects/lockfile/ilockfileserializer.hpp"
#include "liblockfile/yaml/iyamlserializer.hpp"

namespace liblockfile::internal {

class Serializer : public ISerializer {
public:
    Serializer(std::unique_ptr<IYamlSerializer> yaml_serializer, std::unique_ptr<ILockFileSerializer> file_serializer);

    virtual void serialize(const ILockFile & file, const std::string & path) const override;

private:
    std::unique_ptr<IYamlSerializer> yaml_serializer;
    std::unique_ptr<ILockFileSerializer> file_serializer;
};

}