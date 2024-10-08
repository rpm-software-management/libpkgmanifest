%module libpkgmanifest
#pragma SWIG nowarn=362,509

%pythoncode %{
def add_property_accessors(target_cls, src_cls=None, src_getter=None):
    """
    Dynamically creates attributes in the target class based on the getter and setter
    methods of a source class.

    This method inspects the source class for methods with 'get_' and 'set_' prefixes,
    and creates corresponding properties in the target class. If a `src_getter` is provided,
    it is used to obtain an instance of the source class, allowing for delegation of property
    access.

    Args:
        target_cls (type): The class where the properties will be added.
        src_cls (type, optional): The class to inspect for getter and setter methods.
                                  If not provided, the target class is used.
        src_getter (callable, optional): A callable that takes an instance of the target class
                                          and returns an instance of the source class.
                                          This is used for delegating property access.

    Example:
        1. Simplifying Access in the Package Class
        - Before: package.get_size()
        - After calling add_property_accessors(Package): package.size

        2. Delegating Access of Internal Objects
        - Before: package.get_nevra().get_name()
        - After calling add_property_accessors(Package, Nevra, Package.get_nevra): package.name
    """
    def create_getter(getter_name):
        def getter(self):
            getter_target = src_getter(self) if src_getter else self
            return getattr(getter_target, getter_name)() if getter_name in dir(getter_target) else None
        return getter

    def create_setter(setter_name):
        def setter(self, value):
            setter_target = src_getter(self) if src_getter else self
            return getattr(setter_target, setter_name)(value) if setter_name in dir(setter_target) else None
        return setter

    if not src_cls:
        src_cls = target_cls

    getter_prefix = 'get_'
    setter_prefix = 'set_'
    attrs = {method[len(getter_prefix):] for method in dir(src_cls) if method.startswith(getter_prefix) or method.startswith(setter_prefix)}
    for attr in attrs:
        getter_name = getter_prefix + attr
        setter_name = setter_prefix + attr
        setattr(target_cls, attr, property(
            create_getter(getter_name),
            create_setter(setter_name)
        ))
%}

// Helper functions for implementing the Python iterator API based on the existing C++ iterator.
%pythoncode %{
class Iterator:
    def __init__(self, container, begin, end):
        self.container = container
        self.cur = begin
        self.end = end

    def __iter__(self):
        return self

    def __next__(self):
        if self.cur == self.end:
            raise StopIteration
        else:
            value = self.cur.value()
            self.cur.next()
            return value
%}

%define add_iterator(ClassName)
%pythoncode %{
def ClassName##__iter__(self):
    return Iterator(self, self.begin(), self.end())
ClassName.__iter__ = ClassName##__iter__
del ClassName##__iter__
%}
%enddef

%include <exception.i>
%include <stdint.i>
%include <std_map.i>
%include <std_string.i>
%include <std_vector.i>

%exception {
    try {
        $action
    } catch (const std::runtime_error & e) {
        SWIG_exception(SWIG_RuntimeError, e.what());
    }
}

%ignore std::vector::vector(size_type);
%ignore std::vector::vector(unsigned int);
%ignore std::vector::resize;

%{
    #include "libpkgmanifest/objects/checksum.hpp"
    #include "libpkgmanifest/objects/manifest.hpp"
    #include "libpkgmanifest/objects/module.hpp"
    #include "libpkgmanifest/objects/nevra.hpp"
    #include "libpkgmanifest/objects/package.hpp"
    #include "libpkgmanifest/objects/packages.hpp"
    #include "libpkgmanifest/objects/repository.hpp"
    #include "libpkgmanifest/objects/repositories.hpp"
    #include "libpkgmanifest/objects/version.hpp"
    #include "libpkgmanifest/operations/parser.hpp"
    #include "libpkgmanifest/operations/serializer.hpp"
%}

%include "libpkgmanifest/objects/checksum.hpp"
%include "libpkgmanifest/objects/module.hpp"
%include "libpkgmanifest/objects/nevra.hpp"
%include "libpkgmanifest/objects/version.hpp"

%include "libpkgmanifest/objects/repository.hpp"

%rename(next) libpkgmanifest::RepositoriesIterator::operator++();
%rename(value) libpkgmanifest::RepositoriesIterator::operator*();
%include "libpkgmanifest/objects/repositories.hpp"
%template(MapRepositories) std::map<std::string, libpkgmanifest::Repository>;
add_iterator(Repositories)

%include "libpkgmanifest/objects/package.hpp"
%template(VectorPackage) std::vector<libpkgmanifest::Package>;

%include "libpkgmanifest/objects/packages.hpp"
%template(MapPackages) std::map<std::string, std::vector<libpkgmanifest::Package>>;

%include "libpkgmanifest/objects/manifest.hpp"

%include "libpkgmanifest/operations/parser.hpp"
%include "libpkgmanifest/operations/serializer.hpp"

%pythoncode %{
add_property_accessors(Checksum)
add_property_accessors(Manifest)
add_property_accessors(Module)
add_property_accessors(Nevra)
add_property_accessors(Package)
add_property_accessors(Repository)
add_property_accessors(Version)
add_property_accessors(Package, Nevra, Package.get_nevra)
%}

// Allow Nevra to be convertible to string
%extend libpkgmanifest::Nevra {
    std::string __str__() {
        return self->to_string();
    }
}

// Adjust Packages for a more convenient Python API
%extend libpkgmanifest::Packages {
    std::vector<libpkgmanifest::Package> __getitem__(const std::string & key) const {
        return self->get(key);
    }

    std::vector<libpkgmanifest::Package> values() {
        return self->get();
    }
}

// Adjust Repositories for a more convenient Python API
%extend libpkgmanifest::Repositories {
    libpkgmanifest::Repository __getitem__(const std::string & id) const {
        return self->get(id);
    }

    void __setitem__(const std::string & id, libpkgmanifest::Repository & repository) {
        self->add(repository);
    }

    bool __contains__(const std::string & id) {
        return self->contains(id);
    }

    std::size_t __len__() {
        return self->size();
    }
};