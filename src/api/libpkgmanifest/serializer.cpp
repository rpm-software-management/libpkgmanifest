#include "manifest_impl.hpp"

#include "libpkgmanifest/common/exception.hpp"
#include "libpkgmanifest/operations/serializer.hpp"

#include "impl/libpkgmanifest/objects/manifest/manifestfactory.hpp"
#include "impl/libpkgmanifest/operations/serializerfactory.hpp"

#include <format>

namespace libpkgmanifest {

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

void Serializer::serialize(const Manifest & manifest, const std::string & path) const {
    try {
        p_impl->serializer->serialize(*manifest.p_impl->get(), path);
    } catch (const std::runtime_error & error) {
        throw SerializerError(std::format("An error occurred during serialization of the manifest file at \"{}\": {}", path, error.what()));
    }
}

}