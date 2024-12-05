%module common
#pragma SWIG nowarn=362,509

%include "shared.i"

%{
    #include "libpkgmanifest/common/repository.hpp"
    #include "libpkgmanifest/common/repositories.hpp"
    #include "libpkgmanifest/common/version.hpp"
%}

%include "libpkgmanifest/common/version.hpp"
%include "libpkgmanifest/common/repository.hpp"

%rename(next) libpkgmanifest::common::RepositoriesIterator::operator++();
%rename(value) libpkgmanifest::common::RepositoriesIterator::operator*();
%include "libpkgmanifest/common/repositories.hpp"
%template(MapRepositories) std::map<std::string, libpkgmanifest::common::Repository>;
add_iterator(Repositories)

%pythoncode %{
add_property_accessors(Repository)
add_property_accessors(Version)
%}

// Adjust Repositories for a more convenient Python API
%extend libpkgmanifest::common::Repositories {
    libpkgmanifest::common::Repository __getitem__(const std::string & id) const {
        return self->get(id);
    }

    void __setitem__(const std::string & id, libpkgmanifest::common::Repository & repository) {
        self->add(repository);
    }

    bool __contains__(const std::string & id) {
        return self->contains(id);
    }

    std::size_t __len__() {
        return self->size();
    }
}
