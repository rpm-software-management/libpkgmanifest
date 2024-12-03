#pragma once

#include "impl/libpkgmanifest/objects/repositories/irepositories.hpp"
#include "impl/libpkgmanifest/objects/version/iversion.hpp"

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace libpkgmanifest::internal {

class IInput {
public:
    virtual ~IInput() = default;

    virtual std::unique_ptr<IInput> clone() const = 0;

    virtual std::string get_document() const = 0;
    virtual const IVersion & get_version() const = 0;
    virtual IVersion & get_version() = 0;
    virtual const IRepositories & get_repositories() const = 0;
    virtual IRepositories & get_repositories() = 0;
    virtual const std::map<std::string, std::vector<std::string>> & get_packages() const = 0;
    virtual std::map<std::string, std::vector<std::string>> & get_packages() = 0;
    virtual const std::map<std::string, std::vector<std::string>> & get_modules() const = 0;
    virtual std::map<std::string, std::vector<std::string>> & get_modules() = 0;
    virtual const std::vector<std::string> & get_archs() const = 0;
    virtual std::vector<std::string> & get_archs() = 0;

    virtual void set_document(const std::string & document) = 0;
    virtual void set_version(std::unique_ptr<IVersion> version) = 0;
    virtual void set_repositories(std::unique_ptr<IRepositories> repositories) = 0;
};

}