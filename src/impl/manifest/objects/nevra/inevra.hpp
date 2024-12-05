#pragma once

#include <memory>
#include <string>

namespace libpkgmanifest::internal::manifest {

class INevra {
public:
    virtual ~INevra() = default;

    virtual std::unique_ptr<INevra> clone() const = 0;

    virtual std::string get_name() const = 0;
    virtual std::string get_epoch() const = 0;
    virtual std::string get_version() const = 0;
    virtual std::string get_release() const = 0;
    virtual std::string get_arch() const = 0;

    virtual void set_name(const std::string & name) = 0;
    virtual void set_epoch(const std::string & epoch) = 0;
    virtual void set_version(const std::string & version) = 0;
    virtual void set_release(const std::string & release) = 0;
    virtual void set_arch(const std::string & arch) = 0;

    virtual std::string to_string() const = 0;
    virtual std::string to_evr_string() const = 0;
};

}