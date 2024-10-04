#include "repository.hpp"

namespace libpkgmanifest::internal {

Repository::Repository()
    : id()
    , url() {}

std::unique_ptr<IRepository> Repository::clone() const {
    return std::unique_ptr<IRepository>(new Repository(*this));
}

std::string Repository::get_id() const {
    return id;
}

std::string Repository::get_url() const {
    return url;
}

void Repository::set_id(const std::string & id) {
    this->id = id;
}

void Repository::set_url(const std::string & url) {
    this->url = url;
}

}