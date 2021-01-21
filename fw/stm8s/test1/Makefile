DEVICE        = stm8s103f3
F_CPU        ?= 16000000

## A directory for stm8s include file & lib
COMMONDIR = ../common

## Get program name from enclosing directory name
PROGRAM = $(lastword $(subst /, ,$(CURDIR)))

SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.rel)
HEADERS=$(wildcard *.h $(COMMONDIR)/inc/*.h)

CC = sdcc
PROGRAMMER = stlinkv2

DEFINES=
DEFINES += -DSTM8S103

CPPFLAGS =  -I$(COMMONDIR)/inc
CFLAGS = --Werror --std-sdcc99 -mstm8 --opt-code-size $(DEFINES) -DF_CPU=$(F_CPU)UL
LDFLAGS = -lstm8 -mstm8 --out-fmt-ihx
LDLIBS = -L$(COMMONDIR) -lcommon.lib

.PHONY: all clean flash

all: $(PROGRAM).ihx
	@echo $(SOURCES)
	exit
	@ls -la $(PROGRAM).ihx

$(PROGRAM).ihx: $(OBJECTS) $(COMMONDIR)/common.lib
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(COMMONDIR)/common.lib:
	@make -C $(COMMONDIR) all

%.rel : %.c $(HEADERS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

CCOMPILEDFILES=$(SOURCES:.c=.asm) $(SOURCES:.c=.lst) $(SOURCES:.c=.rel) \
               $(SOURCES:.c=.rst) $(SOURCES:.c=.sym)
clean:
	@rm -f $(PROGRAM).ihx $(PROGRAM).cdb $(PROGRAM).lk $(PROGRAM).map $(CCOMPILEDFILES)

flash: $(PROGRAM).ihx
	stm8flash -c $(PROGRAMMER) -p $(DEVICE) -w $(PROGRAM).ihx
