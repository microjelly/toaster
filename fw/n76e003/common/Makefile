DFOSC  = -DFOSC_160000
DFONTSET_MINI ?= -DFONTSET_MINI

SRCDIR = ./src
INCDIR = ./inc

## Get program name from enclosing directory name
PROGRAM = $(lastword $(subst /, ,$(CURDIR)))

SOURCES=$(wildcard *.c $(SRCDIR)/*.c)
OBJECTS=$(SOURCES:.c=.rel)
HEADERS=$(wildcard *.h $(INCDIR)/*.h)

CC = sdcc
AS = sdas8051
MCU_MODEL = mcs51
MODEL  = small
CODE_SIZE = --code-size 18432
IRAM_SIZE = --iram-size 256
XRAM_SIZE = --xram-size 768

AFLAGS =  -l -s 
CFLAGS = -I$(INCDIR) -m$(MCU_MODEL) --model-$(MODEL) --out-fmt-ihx --no-xinit-opt $(DFOSC) $(DFONTSET_MINI)
LFLAGS = $(LIBPATH) $(LIBS) -m$(MCU_MODEL) --model-$(MODEL) $(CODE_SIZE) $(IRAM_SIZE) $(XRAM_SIZE) --out-fmt-ihx $(DEBUG) $(DFOSC) $(DFONTSET_MINI)

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
