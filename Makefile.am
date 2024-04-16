ACLOCAL_AMFLAGS = -I m4

SUBDIRS = \
	include \
	common \
	libcerror \
	libcnotify \
	libuna \
	libfdatetime \
	libfguid \
	libfusn \
	libftxf \
	po \
	manuals \
	tests \
	ossfuzz \
	msvscpp

DPKG_FILES = \
	dpkg/changelog \
	dpkg/changelog.in \
	dpkg/compat \
	dpkg/control \
	dpkg/copyright \
	dpkg/rules \
	dpkg/libftxf-dev.install \
	dpkg/libftxf.install \
	dpkg/source/format

GETTEXT_FILES = \
	config.rpath \
	po/Makevars.in

PKGCONFIG_FILES = \
	libftxf.pc.in

SPEC_FILES = \
	libftxf.spec \
	libftxf.spec.in

EXTRA_DIST = \
	$(DPKG_FILES) \
	$(GETTEXT_FILES) \
	$(PKGCONFIG_FILES) \
	$(SPEC_FILES)

DISTCLEANFILES = \
	config.status \
	config.cache \
	config.log \
	libftxf.pc \
	libftxf.spec \
	Makefile \
	Makefile.in \
	po/Makevars

pkgconfigdir = $(libdir)/pkgconfig

pkgconfig_DATA = \
	libftxf.pc

libtool: @LIBTOOL_DEPS@
	cd $(srcdir) && $(SHELL) ./config.status --recheck

lib: library

library:
	(cd $(srcdir)/common && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libcerror && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libcnotify && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libuna && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libfdatetime && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libfguid && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libfusn && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libftxf && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/po && $(MAKE) $(AM_MAKEFLAGS))

