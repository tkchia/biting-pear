VPATH = $(conf_Srcdir)

CPPFLAGS := -I$(conf_Srcdir)/include $(CPPFLAGS)
CPPFLAGS_FOR_TARGET := -I$(conf_Srcdir)/include $(CPPFLAGS_FOR_TARGET)

conf_Prefix ?= /usr/local
ifeq "." "$(conf_Srcdir)"
    conf_Separate_build_dir ?= no
else
    conf_Separate_build_dir ?= yes
endif
includedir = $(conf_Prefix)/include

.DEFAULT_GOAL := default

.PHONY: default all check install uninstall clean distclean
