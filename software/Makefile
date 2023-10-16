# Device Definitions
MMCU := atmega328p
F_CPU := 16000000UL

# Uploading flags
PARTMODEL := m328p
PROGRAMMER := usbasp
BAUDRATE := 115200
BITCLOCK := 4
DELAY := 10

# Directories
SRCDIR := src
TSTDIR := tests
INCDIR := include
LIBDIR := lib
BINDIR := bin
OBJDIR := obj
BLDDIR := build
DOCDIR := docs

# Programs
CC1 := avr-gcc
CC2 := avr-objcopy
CC3 := avrdude

# Compiler flags
CFLAGS := -I$(INCDIR) -I$(SRCDIR) -lm -mmcu=$(MMCU) -DF_CPU=$(F_CPU) -Wall

# Sources and expected objects
SRCS := $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/*/*.c) $(wildcard $(SRCDIR)/*/*/*.c) $(wildcard $(SRCDIR)/*/*/*/*.c)
OBJS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

# Test sources and expected objects
TEST_SRCS := $(wildcard $(TSTDIR)/*.c) $(wildcard $(TSTDIR)/*/*.c) $(wildcard $(TSTDIR)/*/*/*.c) $(wildcard $(TSTDIR)/*/*/*/*.c)
TEST_OBJS := $(patsubst $(TSTDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

# Output files
EXECUTABLE := $(BINDIR)/program.elf
HEXCONVERT := $(BINDIR)/program.hex

# -------------------------------------------------------------------
# Main Rule
# ---------
all: $(BINDIR) $(HEXCONVERT)

$(HEXCONVERT): $(EXECUTABLE)
	@echo " [*] Converting to HEX..."
	@$(CC2) -j .text -j .data -O ihex $^ $@
	@echo "     Done."

$(EXECUTABLE): $(OBJS)
	@echo " [*] Linking into executable file..."
	@$(CC1) $(CFLAGS) $^ -Os -o $@ -L$(LIBDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@echo "     [+] Creating  : $(basename $(shell echo $@ | sed 's/[^\/]*$$//'))"
	@mkdir -p $(basename $(shell echo $@ | sed 's/[^\/]*$$//'))
	@echo "     [+] Compiling : $<"
	@$(CC1) $(CFLAGS) -c $< -Os -o $@

$(OBJDIR):
	@echo " [*] Preparing to compile process..."
	@mkdir -p $(OBJDIR)

$(BINDIR):
	@mkdir -p $(BINDIR)

# ---------------
# Docs build Rule
# ---------------
docs:
	@echo " [*] Building documentation..."
	@doxygen Doxyfile > /dev/null 2>&1
	@echo "     Done."

# -----------
# Upload Rule
# -----------
upload: all
	@echo " [*] Uploading..."
	@$(CC3) -c $(PROGRAMMER) -p $(PARTMODEL) -U flash:w:$(HEXCONVERT) -i $(DELAY) -b $(BAUDRATE) -B $(BITCLOCK)

# ----------
# Clean Rule
# ----------
clean:
	@echo " [*] Cleaning..."
	@echo "     [+] Removing: $(BINDIR)/"
	@rm -rf $(BINDIR)
	@echo "     [+] Removing: $(OBJDIR)/"
	@rm -rf $(OBJDIR)
	@echo "     [+] Removing: $(BLDDIR)/"
	@rm -rf $(BLDDIR)
	@echo "     [+] Removing: $(DOCDIR)/"
	@rm -rf $(DOCDIR)


.PHONY: all clean
