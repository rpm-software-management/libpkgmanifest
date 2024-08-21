#include "manifest_impl.hpp"

#include "libpkgmanifest/serializer.hpp"

#include "libpkgmanifest/objects/manifest/manifestfactory.hpp"
#include "libpkgmanifest/operations/serializerfactory.hpp"

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
    p_impl->serializer->serialize(*manifest.p_impl->get(), path);
}

}