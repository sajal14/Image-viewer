## Process this file with automake to produce Makefile.in

## Created by Anjuta

uidir = $(datadir)/image_viewer/ui
ui_DATA = image_viewer.ui

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	$(IMAGE_VIEWER_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = image_viewer

image_viewer_SOURCES = \
	callbacks.c \
	callbacks.h \
	main.c

image_viewer_LDFLAGS = \
	-Wl,--export-dynamic

image_viewer_LDADD = $(IMAGE_VIEWER_LIBS)

EXTRA_DIST = $(ui_DATA)

# Remove ui directory on uninstall
uninstall-local:
	-rm -r $(uidir)
	-rm -r $(datadir)/image_viewer
