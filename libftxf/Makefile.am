AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBFDATETIME_CPPFLAGS@ \
	@LIBFGUID_CPPFLAGS@ \
	@LIBFUSN_CPPFLAGS@ \
	@LIBFTXF_DLL_EXPORT@

lib_LTLIBRARIES = libftxf.la

libftxf_la_SOURCES = \
	ftxf_record.h \
	libftxf.c \
	libftxf_debug.c libftxf_debug.h \
	libftxf_definitions.h \
	libftxf_extern.h \
	libftxf_error.c libftxf_error.h \
	libftxf_libcerror.h \
	libftxf_libcnotify.h \
	libftxf_libfdatetime.h \
	libftxf_libfguid.h \
	libftxf_libfusn.h \
	libftxf_libuna.h \
	libftxf_record.c libftxf_record.h \
	libftxf_support.c libftxf_support.h \
	libftxf_types.h \
	libftxf_unused.h

libftxf_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBFDATETIME_LIBADD@ \
	@LIBFGUID_LIBADD@ \
	@LIBFUSN_LIBADD@

libftxf_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libftxf_definitions.h.in \
	libftxf.rc \
	libftxf.rc.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f libftxf_definitions.h
	/bin/rm -f libftxf.rc
	/bin/rm -f Makefile

splint:
	@echo "Running splint on libftxf ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libftxf_la_SOURCES)

