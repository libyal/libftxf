AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@LIBFTXF_DLL_IMPORT@

TESTS = \
	test_api_functions.sh \
	test_api_types.sh

check_SCRIPTS = \
	test_api_functions.sh \
	test_api_types.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	ftxf_test_error \
	ftxf_test_get_version \
	ftxf_test_record

ftxf_test_error_SOURCES = \
	ftxf_test_error.c \
	ftxf_test_libcstring.h \
	ftxf_test_libftxf.h \
	ftxf_test_macros.h \
	ftxf_test_unused.h

ftxf_test_error_LDADD = \
	../libftxf/libftxf.la \
	@LIBCSTRING_LIBADD@

ftxf_test_get_version_SOURCES = \
	ftxf_test_get_version.c \
	ftxf_test_libcstring.h \
	ftxf_test_libftxf.h \
	ftxf_test_macros.h \
	ftxf_test_unused.h

ftxf_test_get_version_LDADD = \
	../libftxf/libftxf.la \
	@LIBCSTRING_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

ftxf_test_record_SOURCES = \
	ftxf_test_record.c \
	ftxf_test_libcstring.h \
	ftxf_test_libftxf.h \
	ftxf_test_macros.h \
	ftxf_test_memory.c ftxf_test_memory.h \
	ftxf_test_unused.h

ftxf_test_record_LDADD = \
	../libftxf/libftxf.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

distclean: clean
	/bin/rm -f Makefile

