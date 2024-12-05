#pragma once

#include "inevra.hpp"

namespace libpkgmanifest::internal::manifest {

class Nevra : public INevra {
public:
    Nevra();

    virtual std::unique_ptr<INevra> clone() const override;

    virtual std::string get_name() const override;
    virtual std::string get_epoch() const override;
    virtual std::string get_version() const override;
    virtual std::string get_release() const override;
    virtual std::string get_arch() const override;

    virtual void set_name(const std::string & name) override;
    virtual void set_epoch(const std::string & epoch) override;
    virtual void set_version(const std::string & version) override;
    virtual void set_release(const std::string & release) override;
    virtual void set_arch(const std::string & arch) override;

    virtual std::string to_string() const override;
    virtual std::string to_evr_string() const override;

private:
    std::string name;
    std::string epoch;
    std::string version;
    std::string release;
    std::string arch;
};

}