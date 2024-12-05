#include "manifest_impl.hpp"

#include "libpkgmanifest/common/exception.hpp"
#include "libpkgmanifest/manifest/serializer.hpp"

#include "impl/manifest/objects/manifest/manifestfactory.hpp"
#include "impl/manifest/operations/serializer/serializerfactory.hpp"

#include <format>

namespace libpkgmanifest::manifest {

using namespace libpkgmanifest::internal::manifest;

class Serializer::Impl {
public:
    Impl() {
        serializer = SerializerFactory().create();
    }
private:
    friend Serializer;
    std::unique_ptr<ISerializer> serializer;
};

Serializer::Serializer() : p_impl(std::make_unique<Impl>()) {}

Serializer::~Serializer() = default;

void Serializer::serialize(const Manifest & manifest, const std::string & path) const {
    try {
        p_impl->serializer->serialize_manifest(*manifest.p_impl->get(), path);
    } catch (const std::runtime_error & error) {
        throw SerializerError(std::format("An error occurred during serialization of the manifest file at \"{}\": {}", path, error.what()));
    }
}

}