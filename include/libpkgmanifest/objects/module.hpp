#pragma once

#include <memory>
#include <string>

namespace libpkgmanifest {

/// @brief A structure that holds modularity-related information about the package.
/// @note For more details, refer to the official Modularity project documentation: https://docs.fedoraproject.org/en-US/modularity/.
class Module {
public:
    Module();
    ~Module();

    Module(const Module & other);
    Module & operator=(const Module & other);

    Module(Module && other) noexcept;
    Module & operator=(Module && other) noexcept;

    /// @brief Retrieves the Name of the module to which the package belongs.
    /// @return A string representing the module name.
    std::string get_name() const;

    /// @brief Retrieves the stream identifier, which indicates the specific version or variant of the module.
    /// @return A string representing the stream identifier.
    std::string get_stream() const;

    /// @brief Sets the name of the module to which the package belongs.
    /// @param name A string containing the module name.
    void set_name(const std::string & name);

    /// @brief Sets the stream identifier, which typically represents the version or variant of the module.
    /// @param stream A string containing the stream identifier.
    void set_stream(const std::string & stream);

private:
    friend class Package;

    class Impl;
    std::unique_ptr<Impl> p_impl;
};

}