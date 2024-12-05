#pragma once

#include "imodule.hpp"

namespace libpkgmanifest::internal::manifest {

class Module : public IModule {
public:
    Module();

    virtual std::unique_ptr<IModule> clone() const override;

    virtual std::string get_name() const override;
    virtual std::string get_stream() const override;

    virtual void set_name(const std::string & name) override;
    virtual void set_stream(const std::string & stream) override;

private:
    std::string name;
    std::string stream;
};

}