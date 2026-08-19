// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "serializer.hpp"

namespace libpkgmanifest::internal::input {

using namespace libpkgmanifest::internal::common;

Serializer::Serializer(
    std::unique_ptr<IYamlSerializer> yaml_serializer, std::unique_ptr<IInputSerializer> input_serializer)
    : yaml_serializer(std::move(yaml_serializer)),
      input_serializer(std::move(input_serializer)) {}

void Serializer::serialize_input(const IInput & input, const std::string & path) const {
    auto node = input_serializer->serialize(input);
    yaml_serializer->to_file(*node, path);
}

}  // namespace libpkgmanifest::internal::input
