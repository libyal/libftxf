AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBFDATETIME_CPPFLAGS@ \
	@LIBFGUID_CPPFLAGS@ \
	@LIBFUSN_CPPFLAGS@ \
	@LIBFTXF_DLL_IMPORT@

TESTS = \
	test_library.sh

check_SCRIPTS = \
	test_library.sh \
	test_manpage.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	ftxf_test_error \
	ftxf_test_record \
	ftxf_test_support

ftxf_test_error_SOURCES = \
	ftxf_test_error.c \
	ftxf_test_libftxf.h \
	ftxf_test_macros.h \
	ftxf_test_unused.h

ftxf_test_error_LDADD = \
	../libftxf/libftxf.la

ftxf_test_record_SOURCES = \
	ftxf_test_libcerror.h \
	ftxf_test_libftxf.h \
	ftxf_test_macros.h \
	ftxf_test_memory.c ftxf_test_memory.h \
	ftxf_test_record.c \
	ftxf_test_unused.h

ftxf_test_record_LDADD = \
	../libftxf/libftxf.la \
	@LIBCERROR_LIBADD@

ftxf_test_support_SOURCES = \
	ftxf_test_libftxf.h \
	ftxf_test_macros.h \
	ftxf_test_support.c \
	ftxf_test_unused.h

ftxf_test_support_LDADD = \
	../libftxf/libftxf.la

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f Makefile

