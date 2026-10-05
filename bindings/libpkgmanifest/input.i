%module input
#pragma SWIG nowarn=362,509

%include "common.i"

%{
    #include "libpkgmanifest/input/input.hpp"
    #include "libpkgmanifest/input/modules.hpp"
    #include "libpkgmanifest/input/options.hpp"
    #include "libpkgmanifest/input/packages.hpp"
    #include "libpkgmanifest/input/parser.hpp"
    #include "libpkgmanifest/input/serializer.hpp"
%}

%include "libpkgmanifest/input/packages.hpp"
%include "libpkgmanifest/input/modules.hpp"
%include "libpkgmanifest/input/options.hpp"

%include "libpkgmanifest/input/input.hpp"
%include "libpkgmanifest/input/parser.hpp"
%include "libpkgmanifest/input/serializer.hpp"

%pythoncode %{
add_property_accessors(Input)
add_property_accessors(Modules)
add_property_accessors(Options)
add_property_accessors(Packages)

CURRENT_INPUT_SCHEMA_VERSION = Version()
CURRENT_INPUT_SCHEMA_VERSION.set_major(0)
CURRENT_INPUT_SCHEMA_VERSION.set_minor(0)
CURRENT_INPUT_SCHEMA_VERSION.set_patch(2)
%}
