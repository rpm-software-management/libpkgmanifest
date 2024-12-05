#pragma once

#include <memory>

namespace libpkgmanifest::internal::common {

class IVersion {
public:
    virtual ~IVersion() = default;

    virtual std::unique_ptr<IVersion> clone() const = 0;

    virtual unsigned get_major() const = 0;
    virtual unsigned get_minor() const = 0;
    virtual unsigned get_patch() const = 0;

    virtual void set_major(unsigned major) = 0;
    virtual void set_minor(unsigned minor) = 0;
    virtual void set_patch(unsigned patch) = 0;
};

}