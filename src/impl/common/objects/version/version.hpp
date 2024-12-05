#pragma once

#include "iversion.hpp"

namespace libpkgmanifest::internal::common {

class Version : public IVersion {
public:
    Version();

    virtual std::unique_ptr<IVersion> clone() const override;

    virtual unsigned get_major() const override;
    virtual unsigned get_minor() const override;
    virtual unsigned get_patch() const override;

    virtual void set_major(unsigned major) override;
    virtual void set_minor(unsigned minor) override;
    virtual void set_patch(unsigned patch) override;

private:
    unsigned major;
    unsigned minor;
    unsigned patch;
};

}