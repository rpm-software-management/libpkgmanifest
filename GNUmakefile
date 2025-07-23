# This GNU make Makefile is intended as a helper.  meson is used for
# the actual build and configuration, but this GNUmakefile provides
# some useful targets for development and release purposes.  Type
# "gmake help" for more details.  It is called GNUmakefile to indicate
# it requires GNU make.

all:
	@echo "Type 'gmake help' for targets."

authors:
	echo "Authors" > AUTHORS.md
	echo "=======" >> AUTHORS.md
	echo >> AUTHORS.md
	git log --pretty="%aN <%aE>" | env LC_ALL=C sort -u | sed -e 's|^|- |g;G' >> AUTHORS.md

help:
	@echo "libpkgmanifest helper GNUmakefile"
	@echo "The source tree uses meson(1) for building and testing, but this GNUmakefile"
	@echo "is intended as a simple helper for the common steps."
	@echo
	@echo "    authors           Generate a new AUTHORS.md file"

# Quiet errors about target arguments not being targets
%:
	@true
