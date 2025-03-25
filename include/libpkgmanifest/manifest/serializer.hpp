#pragma once

#include "manifest.hpp"

#include <memory>
#include <string>

namespace libpkgmanifest::manifest {

/// @brief A class responsible for serializing the manifest object into a YAML file.
class Serializer {
public:
    Serializer();
    ~Serializer();

    /// @brief Serializes a manifest object to a specified file path.
    ///
    /// @param manifest The manifest object containing package data.
    /// @param path The file path where the manifest should be saved.
    /// @throws SerializerError if an error occurs during serialization.
    void serialize(const Manifest & manifest, const std::string & path) const;

private:
    class Impl;
    std::unique_ptr<Impl> p_impl;
};

}