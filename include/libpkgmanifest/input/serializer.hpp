// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "input.hpp"

#include <memory>
#include <string>

namespace libpkgmanifest::input {

/// @brief A class responsible for serializing the input object into a YAML file.
class Serializer {
public:
    Serializer();
    ~Serializer();

    /// @brief Serializes an input object to a specified file path.
    ///
    /// @param input The input object containing package data.
    /// @param path The file path where the infile should be saved.
    /// @throws SerializerError if an error occurs during serialization.
    void serialize(const Input & input, const std::string & path) const;

private:
    class Impl;
    std::unique_ptr<Impl> p_impl;
};

}  // namespace libpkgmanifest::input
