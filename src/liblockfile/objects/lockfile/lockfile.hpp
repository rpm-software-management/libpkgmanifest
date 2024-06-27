#pragma once

#include "ilockfileinternal.hpp"

#include <memory>

namespace liblockfile {

class LockFile : ILockFileInternal {
public:
    virtual std::string get_document() const override;
    virtual const IVersion & get_version() const override;
    virtual const IPackages & get_packages() const override;

    virtual void set_document(const std::string & document) override;
    virtual void set_version(std::unique_ptr<IVersion> version) override;
    virtual void set_packages(std::unique_ptr<IPackages> packages) override;

private:
    std::string document;
    std::unique_ptr<IVersion> version;
    std::unique_ptr<IPackages> packages;
};

}