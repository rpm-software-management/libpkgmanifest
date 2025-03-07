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
        self.current = begin
        self.end = end

    def __iter__(self):
        return self

    def __next__(self):
        if self.current != self.end:
            value = self.current.value()
            self.current.next()
            return value
        else:
            raise StopIteration
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

// TODO(jkolarik): Temporary workaround for SWIG-related issues.
// See https://github.com/rpm-software-management/libpkgmanifest/issues/33.
%include <std_vector_ext.i>

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
