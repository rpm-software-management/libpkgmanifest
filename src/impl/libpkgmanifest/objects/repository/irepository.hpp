#pragma once

#include <memory>
#include <string>

namespace libpkgmanifest::internal {

class IRepository {
public:
    virtual ~IRepository() = default;

    virtual std::unique_ptr<IRepository> clone() const = 0;

    virtual std::string get_id() const = 0;
    virtual std::string get_baseurl() const = 0;
    virtual std::string get_metalink() const = 0;
    virtual std::string get_mirrorlist() const = 0;

    virtual void set_id(const std::string & id) = 0;
    virtual void set_baseurl(const std::string & baseurl) = 0;
    virtual void set_metalink(const std::string & metalink) = 0;
    virtual void set_mirrorlist(const std::string & mirrorlist) = 0;
};

}