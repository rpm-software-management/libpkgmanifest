#pragma once

#include "libpkgmanifest/objects/repository/irepository.hpp"

#include <map>
#include <memory>
#include <string>

namespace libpkgmanifest::internal {

class IRepositories {
public:
    virtual ~IRepositories() = default;

    virtual std::unique_ptr<IRepositories> clone() const = 0;

    virtual const std::map<std::string, std::unique_ptr<IRepository>> & get() const = 0;
    virtual std::map<std::string, std::unique_ptr<IRepository>> & get() = 0;

    virtual void add(std::unique_ptr<IRepository> repository) = 0;
};

}