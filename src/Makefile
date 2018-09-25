IDIR = -I./u8g2-linux/include -I./forthwith/src -I./forthwith/_build
LDIR = -L./u8g2-linux/bin/ -L./forthwith/_build/
LIBS = -lm -llibu8g2 -lforthwith

CFLAGS = $(IDIR)

SRCS = u8g2x-main.c 

all: sub-u8g2-linux-lib sub-forthwith u8g2x-main

u8g2x-main:
	$(CC) -c -o $@ $(SRCS) $(CFLAGS) $(LDIR) $(LIBS)

sub-u8g2-linux-lib:
	$(MAKE) -C u8g2-linux/ clean
	$(MAKE) -C u8g2-linux/ all

sub-forthwith:
	@echo Compiling ForthWith for target $(FW_TARGET)
	$(MAKE) -C forthwith/ clean
	$(MAKE) -C forthwith/ default

