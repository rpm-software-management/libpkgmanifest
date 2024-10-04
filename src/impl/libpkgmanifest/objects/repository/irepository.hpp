#pragma once

#include <memory>
#include <string>

namespace libpkgmanifest::internal {

class IRepository {
public:
    virtual ~IRepository() = default;

    virtual std::unique_ptr<IRepository> clone() const = 0;

    virtual std::string get_id() const = 0;
    virtual std::string get_url() const = 0;

    virtual void set_id(const std::string & id) = 0;
    virtual void set_url(const std::string & url) = 0;
};

}