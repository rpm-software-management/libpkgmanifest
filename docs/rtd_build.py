import os
import sys
import subprocess

DIR = os.path.abspath(os.path.dirname(__file__))


def configure(src_path, dst_path, substitutions):
    print("Configuring {}...".format(src_path))

    # paths are relative to setup.py location
    src_path = os.path.join(DIR, src_path)
    dst_path = os.path.join(DIR, dst_path)

    data = open(src_path, "r").read()
    for pattern, substitution in substitutions.items():
        data = data.replace(pattern, substitution)
    open(dst_path, "w").write(data)


def generate_bindings_from_dir(in_dir, out_dir):
    swig_options = ["-python", "-doxygen", "-relativeimport", "-outdir", out_dir, "-c++"]
    swig_includes = ["-I" + os.path.join(DIR, "../include"), "-I" + os.path.join(
        DIR, "../common"), "-I/usr/include/python3.12"]

    for in_file in os.listdir(in_dir):
        if in_file.endswith(".i") and in_file not in ["shared.i", "std_vector_ext.i"]:
            print("Generating bindings for: " + in_file)
            subprocess.run(["/usr/bin/swig"] + swig_options + ["-interface", "_" + in_file[:-2]
                                                               ] + swig_includes + [os.path.join(in_dir, in_file)], cwd=DIR, check=True)


def main():
    # configure the .in files
    configure("Doxyfile.in", "Doxyfile", {
              "@CMAKE_SOURCE_DIR@": os.path.join(DIR, "..")})
    configure("conf.py.in", "conf.py", {
              "@CMAKE_CURRENT_BINARY_DIR@": DIR, "@AUTOAPI_EXTENSION@": "\'autoapi.extension\',"})

    # In place replace autodoc directives with autoapidoc directives.
    # Our readthedocs workflow uses autoapidoc instead of autodoc because
    # it is able to parse code generated by swig without including the
    # module -> therefore there is no need for a full build in order to
    # generate python docs.
    for in_file in os.listdir(os.path.join(DIR + "/api/python")):
        if in_file.endswith(".rst"):
            file = os.path.join("api/python/", in_file)
            configure(file, file, {"automodule": "autoapimodule"})

    # run doxygen manually
    print("Running doxygen...")
    subprocess.run(["doxygen"], cwd=DIR, check=True)

    # run swig manually to generate Python bindings which are then used to generate Python API docs
    print("Running SWIG...")

    # libpkgmanifest
    # Generate bindings outside of doc dir, into their python bindings dir. This has to match with path provided to autoapi_dirs in conf.py.in
    generate_bindings_from_dir(os.path.join(
        DIR + "/../bindings/libpkgmanifest"), os.path.join(DIR + "/../bindings/python/libpkgmanifest"))


if __name__ == "__main__":
    if os.environ.get("READTHEDOCS") != "True":
        print("This script is supposed to be used only to build documentation in Read the Docs.")
        print("Use cmake && make doc instead to build documentation locally")
        sys.exit(1)
    main()
