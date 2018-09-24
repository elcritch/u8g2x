
# Chosse proper compiler for your PI
# NanoPi:             arm-none-linux-gnueabi-gcc
# Raspberry Pi Zero:  arm-none-linux-gnueabi-gcc

# Raspberry Pi 2:     arm-none-linux-gnueabihf-gcc
# OrangePi Zero:      arm-none-linux-gnueabihf-gcc
# NanoPi NEO:         arm-none-linux-gnueabihf-gcc
# NanoPi NEO Plus 2:  arm-none-linux-gnueabihf-gcc
# CC=arm-none-linux-gnueabihf-gcc

IDIR= -I ./include
SRCDIR = u8g2src
OBJDIR = obj
OUTDIR = bin
LDIR= -L./obj
LIBS= -lm

CFLAGS= $(IDIR)

SOURCES=$(wildcard $(SRCDIR)/*.c)
OBJECTS=$(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SOURCES:.c=.o))

all: directories $(OUTDIR)/libu8g2.a

i2c-oled: $(OBJECTS) i2c.o
	@echo Generating $(TARGET) ...
	@$(CC) -o $(OUTDIR)/$@ $(OBJ) $(LDIR) $(LIBS)

$(OUTDIR)/libu8g2.a: $(OBJECTS)
	@echo Generating $@ ...
	ar rcs $@ $^

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


$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

directories:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OUTDIR)

