# Makefile for Feta

NAME=feta

CPPSOURCES=list memory string log fetatest
ASOURCES=

LIBS=

# ----

-include ../make-base/make-base.mk
-include ../make-base/make-lib.mk

CFLAGS+=-nostdlib $(if $(CACHE_LENGTH), -D CACHE_LENGTH=$(CACHE_LENGTH)) -fno-rtti -fPIC
