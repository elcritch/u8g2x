IDIR = -Iu8g2-linux/include -Iforthwith/src -Iforthwith/_build
LDIR = -Lu8g2-linux/bin/ -Lforthwith/_build/
LIBS = -lm -llibu8g2 -lforthwith

CFLAGS = $(IDIR)

all: sub-u8g2-linux-lib sub-forthwith u8g2x-main test-example

u8g2x-main: u8g2x-main.c 
	$(CC) -o $@ $^ $(CFLAGS) $(LDIR) $(LIBS)

test-example: sub-u8g2-linux-lib 
	$(CC) -o $@ test-example.c $(CFLAGS) $(LDIR) -lu8g2

sub-u8g2-linux-lib:
	@echo Compiling U8G2 
	$(MAKE) -C u8g2-linux/ all

sub-forthwith:
	@echo Compiling ForthWith 
	$(MAKE) -C forthwith/ default

clean:
	$(MAKE) -C u8g2-linux/ clean
	$(MAKE) -C forthwith/ clean
	rm -Rf test-example
	rm -Rf u8g2x-main


