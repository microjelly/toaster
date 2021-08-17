## A directory for n76e003 include file & lib
COMMONDIR = ../common

## Get program name from enclosing directory name
PROGRAM = $(lastword $(subst /, ,$(CURDIR)))

SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.rel)
HEADERS=$(wildcard *.h $(COMMONDIR)/inc/*.h)

CC = sdcc
AS = sdas8051
MCU_MODEL = mcs51
MODEL  = small
CODE_SIZE = --code-size 18432
IRAM_SIZE = --iram-size 256
XRAM_SIZE = --xram-size 768
DFOSC = -DFOSC_160000

AFLAGS =  -l -s 
CPPFLAGS =  -I$(COMMONDIR)/inc
CFLAGS = -I$(INCDIR) -m$(MCU_MODEL) --model-$(MODEL) --out-fmt-ihx --no-xinit-opt  $(DFOSC)
LFLAGS = $(LIBPATH) $(LIBS) -m$(MCU_MODEL) --model-$(MODEL) $(CODE_SIZE) $(IRAM_SIZE) $(XRAM_SIZE) --out-fmt-ihx $(DEBUG) $(DFOSC)
LDLIBS = -L$(COMMONDIR) -lcommon.lib

FLASHTOOL=nuvoprog

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

flash: $(PROGRAM).ihx
	$(FLASHTOOL) -c $(PROGRAMMER) -p $(DEVICE) -w $(PROGRAM).ihx

clean:
	@rm -f $(PROGRAM).ihx $(PROGRAM).cdb $(PROGRAM).lk $(PROGRAM).map $(CCOMPILEDFILES)
