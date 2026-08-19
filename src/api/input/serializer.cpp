// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "libpkgmanifest/input/serializer.hpp"

#include "impl/input/operations/serializer/serializerfactory.hpp"
#include "input_impl.hpp"
#include "libpkgmanifest/common/exception.hpp"

#include <format>

namespace libpkgmanifest::input {

using namespace libpkgmanifest::internal::input;

class Serializer::Impl {
public:
    Impl() { serializer = SerializerFactory().create(); }

private:
    friend Serializer;
    std::unique_ptr<ISerializer> serializer;
};

Serializer::Serializer() : p_impl(std::make_unique<Impl>()) {}

Serializer::~Serializer() = default;

void Serializer::serialize(const Input & input, const std::string & path) const {
    try {
        p_impl->serializer->serialize_input(*input.p_impl->get(), path);
    } catch (const std::runtime_error & error) {
        throw SerializerError(
            std::format("An error occurred during serialization of the input file at \"{}\": {}", path, error.what()));
    }
}

}  // namespace libpkgmanifest::input
