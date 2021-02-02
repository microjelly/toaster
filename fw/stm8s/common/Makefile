DEVICE        = stm8s103f3
F_CPU        ?= 16000000
OLED         ?= SSD1306_128_64
FONTSET_MINI ?= FONTSET_MINI

SRCDIR = ./src
INCDIR = ./inc

## Get program name from enclosing directory name
PROGRAM = $(lastword $(subst /, ,$(CURDIR)))

SOURCES=$(wildcard *.c $(SRCDIR)/*.c)
OBJECTS=$(SOURCES:.c=.rel)
HEADERS=$(wildcard *.h $(INCDIR)/*.h)

CC = sdcc
PROGRAMMER = stlinkv2

DEFINES=
DEFINES += -DSTM8S103

CPPFLAGS = -I$(INCDIR)
CFLAGS = --Werror --std-sdcc99 -mstm8 --opt-code-size $(DEFINES) -DF_CPU=$(F_CPU)UL -D$(OLED) -D$(FONTSET_MINI)
AR = sdar
ARFLAGS = -rc

.PHONY: all clean flash

all: $(PROGRAM).lib

$(PROGRAM).lib: $(OBJECTS)
	$(AR) $(ARFLAGS) $(PROGRAM).lib $^

%.rel : %.c $(HEADERS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

CCOMPILEDFILES=$(SOURCES:.c=.asm) $(SOURCES:.c=.lst) $(SOURCES:.c=.rel) \
               $(SOURCES:.c=.rst) $(SOURCES:.c=.sym)
clean:
	@rm -f $(PROGRAM).lib $(PROGRAM).cdb $(PROGRAM).lk $(PROGRAM).map $(CCOMPILEDFILES)
