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
	/bin/rm -f libftxf.h
	/bin/rm -f libftxf/definitions.h
	/bin/rm -f libftxf/types.h
	/bin/rm -f Makefile

