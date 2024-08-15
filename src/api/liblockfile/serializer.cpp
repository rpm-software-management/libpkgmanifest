#include "lockfile_impl.hpp"

#include "liblockfile/serializer.hpp"

#include "liblockfile/objects/lockfile/lockfilefactory.hpp"
#include "liblockfile/operations/serializerfactory.hpp"

namespace liblockfile {

class Serializer::Impl {
public:
    Impl() {
        serializer = internal::SerializerFactory().create();
    }
private:
    friend Serializer;
    std::unique_ptr<internal::ISerializer> serializer;
};

Serializer::Serializer() : p_impl(std::make_unique<Impl>()) {}

Serializer::~Serializer() = default;

void Serializer::serialize(const LockFile & file, const std::string & path) const {
    p_impl->serializer->serialize(*file.p_impl->get(), path);
}

}