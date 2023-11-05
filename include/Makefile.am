include_HEADERS = \
	libftxf.h

pkginclude_HEADERS = \
	libftxf/codepage.h \
	libftxf/definitions.h \
	libftxf/error.h \
	libftxf/extern.h \
	libftxf/features.h \
	libftxf/types.h

EXTRA_DIST = \
	libftxf.h.in \
	libftxf/definitions.h.in \
	libftxf/features.h.in \
	libftxf/types.h.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f libftxf.h
	-rm -f libftxf/definitions.h
	-rm -f libftxf/features.h
	-rm -f libftxf/types.h
	-rm -f Makefile

