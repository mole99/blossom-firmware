CC         = avr-gcc
MCU        = attiny85
CFLAGS     = -Wall -Os -mmcu=$(MCU) -DF_CPU=8000000 $(foreach dir, $(SRC_DIRS), -I $(dir))

SRC_DIRS   = src
OBJ_DIR    = obj

HEADERS    := $(foreach dir, $(SRC_DIRS), $(shell find $(dir) -name "*.h"))
C_SRC      := $(foreach dir, $(SRC_DIRS), $(shell find $(dir) -name "*.c"))
OBJECTS    := $(addprefix $(OBJ_DIR)/, $(C_SRC:.c=.o))

DIRS       := $(BUILD_DIR) $(sort $(dir $(OBJECTS)))

default: program.hex

$(OBJECTS) : | $(DIRS)

$(DIRS): 
	@echo Creating $(@)
	@mkdir -p $(@)

$(OBJ_DIR)/%.o: %.c $(HEADERS)
	@echo Compiling $(<F)
	$(CC) -o $@ -c $< $(CFLAGS)

program.elf: $(OBJECTS)
	@echo Linking $(@)
	$(CC) -o $@ $^ $(CFLAGS)

program.hex: program.elf
	@echo Creating $(@)
	avr-objcopy -O ihex -R .eeprom $(<) $(@)

upload: program.hex
	@echo Uploading $(<)
	avrdude -c usbasp -p $(MCU) -P usb -U lfuse:w:0xE2:m -U flash:w:$(<)

reset:
	# Verify fuse parameters, resets device
	@echo Resetting device
	avrdude -c usbasp -p $(MCU) -P usb -U lfuse:v:0xE2:m

size: program.elf
	@echo Printing program size
	avr-size $(<) --format=avr --mcu=$(MCU)

.PHONY: clean upload reset

clean:
	rm -f $(OBJECTS)
	rm -f program.elf program.hex
