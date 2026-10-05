// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "impl/common/yaml/iyamlserializer.hpp"
#include "impl/input/objects/input/iinputserializer.hpp"
#include "iserializer.hpp"

namespace libpkgmanifest::internal::input {

using namespace libpkgmanifest::internal::common;

class Serializer : public ISerializer {
public:
    Serializer(std::unique_ptr<IYamlSerializer> yaml_serializer, std::unique_ptr<IInputSerializer> input_serializer);

    virtual void serialize_input(const IInput & input, const std::string & path) const override;

private:
    std::unique_ptr<IYamlSerializer> yaml_serializer;
    std::unique_ptr<IInputSerializer> input_serializer;
};

}  // namespace libpkgmanifest::internal::input
