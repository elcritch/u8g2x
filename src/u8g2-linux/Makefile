
# Chosse proper compiler for your PI
# NanoPi:             arm-none-linux-gnueabi-gcc
# Raspberry Pi Zero:  arm-none-linux-gnueabi-gcc

# Raspberry Pi 2:     arm-none-linux-gnueabihf-gcc
# OrangePi Zero:      arm-none-linux-gnueabihf-gcc
# NanoPi NEO:         arm-none-linux-gnueabihf-gcc
# NanoPi NEO Plus 2:  arm-none-linux-gnueabihf-gcc
# CC=arm-none-linux-gnueabihf-gcc

IDIR= -I./include
SRCDIR = u8g2src
OBJDIR = obj
OUTDIR = bin
LDIR= -L./obj
LIBS= -lm

CFLAGS= $(IDIR)

U8G2_SRCS=$(wildcard $(SRCDIR)/*.c)
U8G2_OBJS=$(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(U8G2_SRCS:.c=.o))

PERIPHERY_OBJS=$(wildcard c-periphery/obj/*.o)

UL_SRCS= u8g2_linux_impl.c u8g2_linux_spi.c
UL_OBJS=$(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(UL_SRCS:.c=.o))

ARCH := $(shell uname -m)
IS_ARM :=$(filter arm,$(shell uname -m))

ifeq ($(ARCH), x86_64)
FW_TARGET=linux-x86
endif
ifneq ($(IS_ARM),)
FW_TARGET=linux-arm
endif

all: directories $(OUTDIR)/libu8g2.a

$(OUTDIR)/libu8g2.a: $(U8G2_OBJS) $(UL_OBJS) cperiphery
	@echo Generating $@ ...
	ar rcs $@ $(U8G2_OBJS) $(UL_OBJS) $(PERIPHERY_OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS) $(LDIR) $(LIBS)

$(OBJDIR)/$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS) $(LDIR) $(LIBS)

clean:
	@echo RM -rf $(OBJDIR)/
	@rm -rf $(OBJ)
	@rm -rf $(OBJDIR)
	@echo RM -rf $(OUTDIR)/
	@rm -rf $(OUTDIR)
	$(MAKE) -C c-periphery/ clean


$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

directories:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OUTDIR)

cperiphery:
	$(MAKE) -C c-periphery/

subforthwith:
	@echo Compiling ForthWith for target $(FW_TARGET)
	$(MAKE) -C forthwith/ clean
	$(MAKE) -C forthwith/ default

