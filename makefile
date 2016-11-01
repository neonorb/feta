# Makefile for Feta

NAME=feta

CSOURCES=list memory string log fetatest
ASOURCES=

LIBS=

# ----

-include ../make-base/make-base.mk
-include ../make-base/make-lib.mk

CFLAGS+=-nostdlib
